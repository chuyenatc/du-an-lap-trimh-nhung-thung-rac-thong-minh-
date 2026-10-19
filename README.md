# 🗑️ Dự án: Thùng Rác Thông Minh (Smart Trash Can)

<p align="center">
  <i>Bài tập lớn môn: Xây dựng các hệ thống nhúng - Trường Đại học Công nghệ GTVT[cite: 2]</i><br>
  <i>Giảng viên hướng dẫn: Trần Minh Hạnh[cite: 2]</i><br>
  <i>Năm học: 2025-2026[cite: 2]</i>
</p>

## 📖 Giới thiệu
Dự án "Thùng rác thông minh" được phát triển nhằm tự động hóa việc xử lý rác thải trong sinh hoạt, giải quyết các hạn chế của thùng rác truyền thống như: phải mở nắp bằng tay gây mất vệ sinh và không kiểm soát được lượng rác dẫn đến quá tải, rơi vãi rác ra ngoài[cite: 2]. 

Hệ thống sử dụng vi điều khiển Arduino làm bộ xử lý trung tâm[cite: 2], kết hợp với các cảm biến siêu âm để nhận diện người dùng và đo lường khoảng cách đến rác[cite: 2]. Qua đó, thùng rác có khả năng tự động đóng/mở nắp, giám sát mức rác và hiển thị trạng thái trực quan[cite: 2].

## 🛠 Linh kiện phần cứng
* **Board điều khiển trung tâm:** Arduino Uno R3 (01 chiếc)[cite: 2].
* **Cảm biến khoảng cách:** Cảm biến siêu âm HC-SR04 (02 chiếc - 1 đo người, 1 đo rác)[cite: 2].
* **Động cơ điều khiển nắp:** Servo SG90 (Lực kéo 1.6kg/cm, góc quay 0 - 180 độ) (01 chiếc)[cite: 2].
* **Màn hình hiển thị:** OLED 0.96 inch (Giao tiếp I2C, độ phân giải 128x64) (01 chiếc)[cite: 2].
* **Đèn cảnh báo:** 3 đèn LED 5mm (Xanh, Vàng, Đỏ)[cite: 2].
* **Nút bấm (Manual Mode):** Nút nhấn 4 chân[cite: 2], sử dụng điện trở kéo lên nội bộ `INPUT_PULLUP`[cite: 2].
* **Nguồn cấp:** Pin 9V hoặc Adapter 5V/2A[cite: 2].

## 🔌 Sơ đồ đấu nối (Pin Mapping)
Sơ đồ kết nối dây giữa board Arduino và các module ngoại vi[cite: 2]:

| Linh kiện | Chân tín hiệu | Kết nối trên Arduino |
| :--- | :--- | :--- |
| **Cảm biến người**[cite: 2] | Trig / Echo[cite: 2] | Chân 2 / Chân 3[cite: 2] |
| **Cảm biến rác**[cite: 2] | Trig / Echo[cite: 2] | Chân 4 / Chân 5[cite: 2] |
| **Nút bấm**[cite: 2] | Signal[cite: 2] | Chân 6[cite: 2] |
| **Động cơ Servo**[cite: 2] | Signal[cite: 2] | Chân 9[cite: 2] |
| **Đèn LED Xanh**[cite: 2] | Anode (+)[cite: 2] | Chân 10[cite: 2] |
| **Đèn LED Vàng**[cite: 2] | Anode (+)[cite: 2] | Chân 11[cite: 2] |
| **Đèn LED Đỏ**[cite: 2] | Anode (+)[cite: 2] | Chân 12[cite: 2] |
| **Màn hình OLED**[cite: 2] | SDA / SCL[cite: 2] | Chân A4 / Chân A5[cite: 2] |

*(Mạch sử dụng thêm các điện trở 220 Ohm cho đèn LED để bảo vệ thiết bị)*[cite: 2].

## ✨ Chức năng chính & Nguyên lý hoạt động
1. **Tự động đóng/mở nắp (Non-blocking):** Hệ thống phát sóng siêu âm liên tục. Khi phát hiện người ở khoảng cách `<= 3cm`, Servo quay 180 độ để mở nắp[cite: 2]. Khi người rời đi, hệ thống tạo độ trễ 1.5 giây trước khi đóng lại để đảm bảo an toàn[cite: 2]. Mã nguồn sử dụng hàm `millis()` thay cho `delay()` để chương trình không bị chặn, giúp vừa quét cảm biến vừa điều khiển linh kiện khác cùng lúc[cite: 2].
2. **Giám sát mức rác (Cảnh báo LED):** Cảm biến gắn dưới nắp đo khoảng cách tới rác (chiều cao thùng khoảng 15cm)[cite: 2], quy đổi ra % bằng hàm `map()`[cite: 2]:
   * Dưới 50%: Đèn Xanh sáng[cite: 2].
   * Từ 50% - 85%: Đèn Vàng sáng[cite: 2].
   * Trên 85%: Đèn Đỏ sáng (Cảnh báo đầy rác)[cite: 2].
   *(Dữ liệu được cập nhật sau mỗi 15 khung hình (khoảng 0.5s) để chống rung/chớp đèn)*[cite: 2].
3. **Chế độ thủ công (Manual Mode):** Nhấn nút vật lý để nắp mở liên tục, phục vụ việc thay túi rác cho nhân viên vệ sinh mà không bị cảm biến làm phiền[cite: 2]. Nhấn lần nữa để trở lại tự động[cite: 2].
4. **Hiển thị giao diện OLED:** Hiển thị phần trăm rác, trạng thái hoạt động (CÓ NGƯỜI, ĐÃ ĐÓNG, THAY TÚI) và tạo hiệu ứng chữ chạy ngang (Scrolling Text) thông tin tên các thành viên trong nhóm[cite: 2].

## 💻 Hướng dẫn cài đặt (Setup)
1. Tải và cài đặt [Arduino IDE](https://www.arduino.cc/en/software)[cite: 2].
2. Mở trình quản lý thư viện (Library Manager) trong Arduino IDE và cài đặt các thư viện sau[cite: 2]:
   * `Adafruit_SSD1306` (Điều khiển màn hình OLED)[cite: 2].
   * `Adafruit_GFX` (Thư viện đồ họa cho OLED)[cite: 2].
   * `Servo.h` (Thư viện điều khiển Servo - Tích hợp sẵn)[cite: 2].
3. Clone repository này về máy và mở file `.ino`.
4. Kết nối board Arduino Uno với máy tính, chọn đúng mạch `Arduino Uno` và cổng `COM`.
5. Bấm **Upload** để nạp code xuống vi điều khiển.

## 📸 Hình ảnh Demo
*(Bạn hãy lưu ảnh từ file Word vào thư mục `images` của kho lưu trữ để các liên kết này hoạt động)*

| Sơ đồ nguyên lý Proteus/Fritzing | Bố trí cảm biến nắp thùng |
|:---:|:---:|
| ![Sơ đồ nguyên lý](images/sodo.png) | ![Cảm biến siêu âm](images/cambien.png) |

| Toàn cảnh mô hình | Hiển thị màn hình OLED |
|:---:|:---:|
| ![Mô hình hoàn thiện](images/mohinh.png) | ![Màn hình OLED](images/oled.png) |

## 👥 Thành viên nhóm thực hiện (Nhóm 1)
| Họ và Tên | Mã Sinh Viên (Lớp 74DCTT28) |
| :--- | :--- |
| **Đinh Hải Nam**[cite: 2] | 74DCTT28[cite: 2] |
| **Nguyễn Trung Chuyển**[cite: 2] | 74DCTT28[cite: 2] |
| **Vũ Duy Anh**[cite: 2] | 74DCTT28[cite: 2] |
| **Hoàng Minh Hiếu**[cite: 2] | 74DCTT28[cite: 2] |

## 🚀 Hướng phát triển tương lai
* Nâng cấp sử dụng các loại Servo có lực kéo lớn hơn để tương thích với nắp thùng nặng[cite: 2].
* Tích hợp thêm Module WiFi (như ESP8266/ESP32) để gửi thông báo rác đầy qua ứng dụng điện thoại[cite: 2].
* Nghiên cứu và chế tạo cơ cấu tự động nén rác giúp tối ưu hóa không gian bên trong thùng[cite: 2].