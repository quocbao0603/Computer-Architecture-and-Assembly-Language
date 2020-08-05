# Computer Architecture and Assembly Language Project #1 -Project1

## Thông tin tổng quát

### Thành viên nhóm:

- Trần Quốc Bảo - 18120111
- Đoàn Phú Đức - 18120117
- Lê Minh Khoa - 18120415

### Danh sách tính năng

- Số nguyên lớn:
    Kiểu dữ liệu số nguyên lớn QInt có độ lớn 16 byte với các tính năng:
    - Hàm nhập / xuất
    - Hàm chuyển đổi thập phân sang nhị phân
    - Hàm chuyển đổi nhị phân sang thập phân
    - Hàm chuyển đổi thập phân sang thập lục phân
    - Hàm chuyển đổi nhị phân sang thập lục phân
    - Các toán tử: `+`, `-`, `*`, `/`
    - Các toán tử so sánh và gán: `<`, `>`, `<=`, `>=`, `==`, `=`
    - Các toán tử bit: AND `&`, OR `|`, XOR `^`, NOT `~`
    - Các toán tử dịch chuyển: dịch trái `<<`, dịch phải `>>`, xoay trái `rol`, xoay phải `ror`

- Dấu chấm động với độ chính xác cao:
    Kiểu dữ liệu biểu diễn số dấu chấm động có độ chính xác Quadruple-precision với độ lớn 128 bit với các tính năng:
    - Hàm nhập / xuất
    - Hàm chuyển đổi thập phân sang nhị phân
    - Hàm chuyển đổi nhi phân sang thập phân
    - Các toán tử: `+`, `-`, `*`, `/`
    - Xác định các số nhị phân có dạng vô cùng `infinity`, không phải là một số dấu chấm động hợp lệ `NaN` hay số chưa được chuẩn hóa `denormalized`


### Thiết kế chương trình

#### Cấu trúc thư mục

Bài làm được chia thành hai thư mục chính:  
1. Thư mục `Source Code` chứa mã nguồn của QInt và QFloat.  
2. Thư mục `GUI` chứa phần thiết kế giao diện người dùng.  

Kèm theo đó là phần báo cáo được trình bày trong file Report_Project_1.