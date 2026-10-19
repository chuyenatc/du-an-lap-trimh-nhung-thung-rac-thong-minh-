// 1. CHẾ ĐỘ THAY TÚI RÁC (MANUAL MODE) - Đọc nút bấm
  bool currentBtnState = digitalRead(btnPin);
  if (currentBtnState == LOW && lastBtnState == HIGH) {
    manualMode = !manualMode;
    delay(100); // Chống nhiễu phím
  }
  lastBtnState = currentBtnState;

  // 2. ĐO KHOẢNG CÁCH NGƯỜI ĐẾN GẦN
  int distP = getDistance(trigP, echoP);

  // 3. LOGIC ĐIỀU KHIỂN NẮP THÙNG RÁC
  bool isLidOpen = false;

  if (manualMode) {
    myServo.write(180); // Mở nắp cố định
    isLidOpen = true;
  }
  else {
    if (distP > 0 && distP <= 3) { // CHỈNH: Cảm biến người trong tầm 3cm
      myServo.write(180);
      lastTimePersonPresent = millis();
      isLidOpen = true;
    }
    else {
      // Nếu người đi khỏi, đợi đủ 1.5 giây mới đóng nắp
      if (millis() - lastTimePersonPresent > delayClose) {
        myServo.write(45);
        isLidOpen = false;
      } else {
        isLidOpen = true; // Đang trong thời gian chờ đóng
      }
    }
  }

  // 4. ĐO LƯỢNG RÁC VÀ CẢNH BÁO ĐÈN LED
  // Đo lượng rác (Cứ 15 khung hình đo 1 lần để tránh giật máy)
  static int trashLevel = 0;
  static int frameCount = 0;
  if (frameCount++ % 15 == 0) {
    int distT = getDistance(trigT, echoT);
    // CHỈNH: Thùng cao 15cm (Đầy ở 3cm, Rỗng ở 13cm)
    trashLevel = map(distT, 3, 13, 100, 0);
    trashLevel = constrain(trashLevel, 0, 100);
  }

  // ĐIỀU KIỆN ĐÈN LED: Tắt hết khi mở nắp, bật khi đóng nắp
  if (isLidOpen) {
    digitalWrite(ledXanh, LOW); digitalWrite(ledVang, LOW); digitalWrite(ledDo, LOW);
  } else {
    digitalWrite(ledXanh, trashLevel < 50);
    digitalWrite(ledVang, trashLevel >= 50 && trashLevel < 85);
    digitalWrite(ledDo, trashLevel >= 85);
  }

  // 5. HIỂN THỊ MÀN HÌNH OLED
  // Hiệu ứng chữ chạy ngang ở dòng 1
  display.setCursor(scrollX, 0);
  display.print(teamNames);
  scrollX -= 2; // Tốc độ chạy chữ (giảm số để chạy chậm hơn)
  if (scrollX < -(int)(teamNames.length() * 6)) scrollX = 128;

  display.drawLine(0, 10, 128, 10, WHITE); // Đường kẻ phân cách

  display.setCursor(0, 22);
  display.print(F("Muc rac: ")); display.print(trashLevel); display.println(F("%"));

  display.setCursor(0, 42);
  display.print(F("TT: "));
  if (manualMode) display.println(F("THAY TUI"));
  else if (distP <= 3) display.println(F("CO NGUOI"));
  else if (isLidOpen) display.println(F("CHO DONG.."));
  else display.println(F("DA DONG"));

  display.display();