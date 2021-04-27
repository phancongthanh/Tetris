# Tetris
Game Tetris written by C++ and SDL2
## Bao gồm:
- Thư mục "Runtime_win": bao gồm các tệp .dll cho windows.
- Thư mục "Tetris_project": Dự án Tetris sử dụng Code::Block.
- Thư mục "Tetris_Win_x64": Trò chơi Tetris.
## Game gồm 2 thành phần:
- Giao diện cài đặt: Cho phép thay đổi các thông số của game.
- Giao diện game: Phần chơi xếp hình.
## Luồng hoạt động:
- Chạy file: Tetris_Win_x64\Tetris.exe
- Lựa chọn thông số game theo ý muốn.
- "Start" để bắt đầu chơi, alt+F4 thoát game.
- Tại giao game: sử dụng 4 phím mũi tên để điều khiển, F2 để tạm dừng/tiếp tục.
- Sau khi thua hoặc tắt tab game sẽ được chuyển ra giao diện cài đặt.

Xem chi tiết hơn trong: Tetris_Win_x64\Readme.docx
Luật chơi như các game xếp hình khác!
## Tetris project
- Dự án game Tetris sử dụng Code::Block(64bit). Nếu sử dụng 32bit phải đổi link thư viện SDL2.
- Có thể sử dụng makefile để build:
  - Winx64/Winx32: chạy makefile với tham số dòng lệnh Winx64/Winx32 để build.
  - Linux: Đổi khai báo thư viện trong các file SDL_....h trước khi chạy makefile.
  - Thư mục Outfile: chứa file sau khi build.
