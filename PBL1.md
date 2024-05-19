Đề tài PBL 1 : [[Đề tài PBL1]]
# Lời mở đầu
Quy hoạch tuyến tính là một lĩnh vực quan trọng của tối ưu hóa được sử dụngch rộng rãi với nhiều lý do. Nhiều vấn đề ực tế trong nghiên cứu vận hành có thểth được biểu diễn dưới dạng quy hoạch tuyến tính. Một số ờng hợp đặc biệt củtrư a quy hoạ ến tính như tối ưu hoá luồng mạng hay vấn đề phân phát, vậc chuyển chuyển hàng hóa được xem ọng đến mức có nhiều nghiên cứu về các thuật toán chuyên biệt để giải quyết chúng. 

Lịch sử cho thấy rằng ý tưởng từ quy hoạch tuyến tính đã truyền cảm hứng  cho nhiều khái niệm cơ bản trong lý thuyết tối ưu hóa, chẳng hạn như khái niệm đối ngẫu, phân rã và tầm quan trọng của tính lõm hay các tổng quát của nó. Tương tự, quy hoạch tuyến tính đã được sử dụng mạnh mẽ trong giai đoạn đầu của kinh tế học vi mô và hiện đang được sử dụng trong quản lý doanh nghiệp, chẳng hạn như lập kế hoạch, sản xuất, vận chuyển và công nghệ. Mặc dù các vấn đề quản lý hiện đại thay đổi liên tục, hầu hết các công ty vẫn muốn tối đa hóa lợi nhuận và giảm thiểu chi phí với tài nguyên hạn chế. Cụ thể, quy hoạch tuyến tính được ứng dụng trên thực tế với các chủ đề như: 

- Lập kế hoạ sản xuất Xác định lịch trình sản xuất hiệu quả, phối hợp sửa chữa : dụng nguồn lực như máy móc, nhân công và nguyên liệu để tối đa hóa sản lượng. 
- Quản lý dự án: Phân công nguồn lực, lên kế hoạch công việc, và quản lý các ràng buộc thời gian trong quản lý dự án để đạt được hiệu quả và hoàn thành dự án đúng hạn. 
- Quy hoạch Tiếp Thị Xác định chiến lược quảng cáo và phân (Marketing): phối ngân sách tiếp thị sao cho lợi nhuận cao nhất hoặc mục tiêu tiếp thị được.
%%
Phương pháp giải hệ phương trình tuyến tính đã được tìm ra vào năm 1827 bởi Fourier. 

Vào năm 1939, một dạng bài toán quy hoạch tuyến tính tương đương với bài toán quy hoạch tuyến tính tổng quát được đưa ra bởi nhà toán học và kinh tế học Leonid Kantorovich, và ông cũng là người đề xuất phương pháp giải nó. 

Trong toán học, quy hoạch tuyến tính (Linear Programming - LP) là bài toán tối ưu hoá, trong đó hàm mục tiêu (objective function) và các điều kiện ràng buộc đều là tuyến tính.

Quy hoạch tuyến tính có rất nhiều ứng dụng từ việc áp dụng tính bài toán vận tải đến việc áp dụng tối ưu chi phí cho quân sự và tăng tổn thất cho kẻ thù (thế chiến thứ II). Ngoài ra, nó còn được ứng dụng ngay cả trong cuộc sống hằng ngày tối như là đa hoá việc tiết kiệm và giảm thiểu năng lượng điện, chăm sóc sức khoẻ, ....
%%
Với độ phức tạp càng cao, việc tính toán giải các bài toán Quy hoạch tuyến tính không phải là một điều dễ dàng và đòi hỏi rất nhiều thời gian nghiên cứu cũng như tìm hiểu. Giờ đây, với sự phát triển mạnh mẽ của Khoa học kĩ thuật, việc tính toán cũng như giải các bài toán Quy hoạch tuyến tính trở nên dễ dàng hơn, chỉ mất vài giây thậm chí ít hơn để máy tính có thể giải được thay vì bỏ ra hàng giờ như lúc trước. 

**Mục tiêu** : Để hoàn thành tốt mục tiêu mà đồ án đã đề ra ở trên, ta phải tiến hành các công việc sau:
- Tìm hiểu 
- Triển khai ví dụ bằng tay (với hệ phương trình/ bất phương trình tuyến tính tự chọn)
	- Phương pháp Simplex
	- Phương pháp Big-M
- Xây dựng thuật toán. Đánh giá độ phức tạp.
- Đánh giá kết quả.

**Phạm vi và đối tượng nghiên cứu** : Giải bài toán Quy hoạch tuyến tính sử dụng phương pháp Simplex và Big M.

**Phương pháp nghiên cứu** : Để thực hiện các công việc trên, em đã sử dụng các phương pháp nghiên cứu:
- Phương pháp phân tích và tổng hợp lí thuyết.
- Phương pháp nghiên cứu tài liệu.
- Tham khảo ý kiến của giảng viên hướng dẫn.

# 1.        TỔNG QUAN ĐỀ TÀI

{Nội dung A {Font: Time New Roman; thường; cỡ chữ: 13; dãn dòng: 1,3; căn lề: justified}

# 2.        CƠ SỞ LÝ THUYẾT

## 2.1.      Ý tưởng
- Phương pháp Simplex : Giải các bài toán quy hoạch tuyến tính cơ bản.
- Phương pháp Big M: Giải các bài toán quy hoạch tuyến tính với độ phức tạp cao hơn.

## 2.2.      Cơ sở lý thuyết
### 2.2.1.  Simplex
### 2.2.2. Big M

# 3.        TỔ CHỨC CẤU TRÚC DỮ LIỆU VÀ THUẬT TOÁN

## 3.1.      Phát biểu bài toán

- Đầu vào (input): 
	- Nhập từ bàn phím.
	- Tệp chứa ma trận biểu diễn bài toán tối ưu tuyến tính.
- Đâfu ra (output):
	- In ra màn hình.
	- Tệp chứa giá trị tối ưu và chứa tập giá trị các biến đạt giá trị tối ưu.

## 3.2.      Cấu trúc dữ liệu
- Mảng, mảng 2 chiều.
## 3.3.      Thuật toán

Trình bày các thuật toán và phân tích độ phức tạp của các thuật toán.
- [[Độ phức tạp của thuật toán]]: O ((1+k)⋅m⋅n)

# 4.        CHƯƠNG TRÌNH VÀ KẾT QUẢ

## 4.1.      Tổ chức chương trình

## 4.2.      Ngôn ngữ cài đặt
- Sử dụng ngôn ngữ C được biên dịch bằng g++ (MinGW-W 64 x 86_64-ucrt-posix-seh, built by Brecht Sanders, r 5) phiên bản 13.2.0.
## 4.3.      Kết quả

### 4.3.1.     Giao diện chính của chương trình

![[0cd043d3a7ae62bc652c94ab3208bb81_MD5.jpeg]]
### 4.3.2.     Kết quả thực thi của chương trình

![[71b433f7d74589b6eb84cd27d1e1848b_MD5.jpeg]]

Mô tả kết quả thực hiện chương trình.

### 4.3.3.     Nhận xét đánh giá

# 5. KẾT LUẬN VÀ HƯỚNG PHÁT TRIỂN

## 5.1. Kết luận

## 5.2. Hướng phát triển
- Cung cấp thêm trình độ hoạ.
- Giải bài toán tối ưu tuyến tính (min).

# Tài liệu tham khảo
- Quy hoạch tuyến tính - Wikipedia 

# Mục lục
