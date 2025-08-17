# Quản Lý Thư Viện

Một chương trình quản lý thư viện viết bằng **C++**, sử dụng các cấu trúc dữ liệu cơ bản (mảng, danh sách liên kết, cây nhị phân tìm kiếm) để quản lý sách, thẻ độc giả và các hoạt động mượn/trả.  

## Chức năng chính
- Quản lý thẻ độc giả: thêm, xóa, chỉnh sửa, khóa/mở thẻ.
- Quản lý đầu sách & danh mục sách: nhập, tìm kiếm, sắp xếp theo tên/thể loại.
- Mượn sách: kiểm tra điều kiện mượn, giới hạn số lượng, theo dõi quá hạn.
- Trả sách: cập nhật trạng thái sách & độc giả.
- Thống kê:
  - Danh sách độc giả mượn quá hạn.
  - Top 10 sách được mượn nhiều nhất.


## Cài đặt & chạy dự án

### Yêu cầu
- Trình biên dịch **C++11** trở lên:
  - `g++` (Linux, Windows, macOS)
  - hoặc `clang++` (macOS)
- (Tùy chọn) `make` để dễ dàng build.


### Các bước thực hiện

#### Clone hoặc tải project
```bash
git clone https://github.com/hoangngm2083/DSA_Library_Management.git
cd library-management
```
hoặc tải `.zip` và giải nén.


#### Biên dịch

Với Makefile:
```bash
mkdir -p build && cd build && cmake .. && make
```

#### Chạy chương trình
```bash
cd bin && ./Library
```

#### Dọn dẹp file thực thi
```bash
make clean
```
