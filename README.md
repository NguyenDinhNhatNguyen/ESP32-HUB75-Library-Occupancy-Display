# 📊 ESP32 Library Occupancy Display (Smart Gateway UI)

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-F6822B?style=for-the-badge&logo=PlatformIO&logoColor=white)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulator-01CBA3?style=for-the-badge&logo=codeforces&logoColor=white)

Dự án phát triển Giao diện hiển thị thời gian thực cho hệ thống đếm người tại thư viện, sử dụng vi điều khiển ESP32. 

**Người thực hiện:** Nguyễn Đình Nhật Nguyên (MSSV: 23521043)  
**Chuyên ngành:** Kỹ thuật Máy tính - Đại học Công nghệ Thông tin (UIT)

## 📑 Giới thiệu chung
Đây là module "Giao diện vật lý" (Physical UI) được thiết kế để đặt tại cổng thư viện. Hệ thống đóng vai trò như một hàng rào thị giác tự động, hướng dẫn sinh viên ra vào dựa trên sức chứa thực tế của không gian, nhằm thay thế hoàn toàn việc nhắc nhở thủ công của thủ thư.

*Lưu ý: Do nền tảng Wokwi không hỗ trợ trực tiếp LED Matrix P5 HUB75, bản Demo này sử dụng ma trận NeoPixel 64x32. Tuy nhiên, giải thuật Pixel Mapping, Custom Font và State Machine được giữ nguyên để dễ dàng port sang phần cứng thật (HUB75) bằng cách thay thế thư viện ở tầng thấp.*

## ✨ Tính năng nổi bật (Bản Demo)
- **Real-time Occupancy UI:** Hiển thị số lượng người hiện tại theo định dạng `XX/50` ở giữa tâm màn hình.
- **Dynamic Color Cues:** - 🟢 **Xanh lá:** Sức chứa an toàn (<50 người), cho phép đi vào.
  - 🔴 **Đỏ báo động:** Quá tải (≥50 người).
- **Non-blocking State Machine:** Hệ thống không sử dụng các lệnh dừng cứng (`delay` dài hoặc `while(true)`). Giao diện liên tục lắng nghe biến động để cập nhật ngay lập tức.
- **Blinking Alert:** Khi đạt tối đa 50 người, chữ `FULL` sẽ chớp tắt liên tục màu đỏ để tạo sự chú ý.
- **Smart Simulator Logic:** Tích hợp bộ tạo dữ liệu ngẫu nhiên thông minh để mô phỏng luồng người:
  - Bình thường: 70% xác suất có người vào, 30% người ra.
  - Khi thư viện đầy (50 người): Chặn hoàn toàn luồng vào (0%), chỉ cho phép luồng ra (30% xác suất) để hệ thống tự động mở lại cửa.
- **Memory Optimization:** Sử dụng bộ Custom Font 5x3 tự định nghĩa thay vì dùng font thư viện có sẵn để tiết kiệm tối đa dung lượng SRAM của chip.

## 🛠 Cấu trúc dự án
- `main.cpp`: Chứa logic điều khiển chính, thuật toán vẽ (drawSprite) và State Machine.
- `diagram.json`: Cấu hình sơ đồ đấu dây cho trình giả lập Wokwi.
- `wokwi.toml`: Cấu hình môi trường build (PlatformIO) cho Wokwi.

## 🚀 Hướng dẫn chạy thử (Simulator)
1. Cài đặt extension **Wokwi Simulator** trên VS Code.
2. Mở dự án này bằng **PlatformIO**.
3. Build project để tạo ra file `.elf` và `.bin` trong thư mục `.pio/build/esp32dev/`.
4. Mở file `diagram.json` và nhấn nút **Play** của Wokwi để xem hệ thống hoạt động.

---