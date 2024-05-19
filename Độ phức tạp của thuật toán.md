# Phân tích độ phức tạp

## Giai đoạn khởi tạo:
- Đọc bảng: Hàm read_tableau đọc đầu vào từ một tệp, có độ phức tạp thời gian là O (m⋅n) với mm là số hàng và nn là số cột trong bảng. Điều này là do nó liên quan đến việc đọc mỗi phần tử một lần.
- Thêm biến trễ: Hàm add_slack_variables có độ phức tạp là O (m 2), vì nó liên quan đến việc thêm các biến trễ để biến các bất đẳng thức thành đẳng thức và điều chỉnh cấu trúc bảng.

## Phương pháp Big-M:
- Áp dụng Big-M: Hàm big_M điều chỉnh hàm mục tiêu cho các biến nhân tạo, liên quan đến các phép toán trên mỗi phần tử của bảng. Điều này cũng có độ phức tạp thời gian là O (m⋅n).

## Giai đoạn lặp Simplex:
- Tìm cột trục: Hàm find_pivot_column tìm kiếm phần tử âm nhất trong hàng mục tiêu, mất thời gian O (n).
- Tìm hàng trục: Hàm find_pivot_row tính toán các tỷ lệ cho tất cả các hàng, dẫn đến độ phức tạp là O (m).
- Phép toán trục: Hàm pivot_on cập nhật bảng bằng cách thực hiện các phép toán hàng, có độ phức tạp là O (m⋅n) vì nó cập nhật mọi phần tử trong bảng.

## Độ phức tạp lặp

Phương pháp Simplex tiến hành theo từng bước lặp lại, cải thiện giải pháp ở mỗi bước. Số lần lặp cần thiết của phương pháp Simplex được biết là bị giới hạn bởi $$
2^n
$$ trong trường hợp tồi tệ nhất, mặc dù thường thì nó hoạt động tốt hơn nhiều trong thực tế. Đối với mục đích thực tế, số lần lặp có thể được coi là đa thức.

Kết hợp các phép toán trên, mỗi lần lặp của phương pháp Simplex có độ phức tạp là O (m⋅n). Nếu kk là số lần lặp, tổng độ phức tạp trở thành O (k⋅m⋅n)
Tổng độ phức tạp

## Dựa trên phân tích:

    Khởi tạo: O(m⋅n)
    Điều chỉnh phương pháp Big-M: O(m⋅n)
    Giai đoạn lặp Simplex: O(k⋅m⋅n)

Do đó, tổng độ phức tạp của thuật toán là O ((1+k)⋅m⋅n) .
# Kết luận

Tóm lại, độ phức tạp của phương pháp Simplex với sự cải tiến Big-M để xử lý các ràng buộc lớn hơn hoặc bằng chủ yếu được quyết định bởi giai đoạn lặp. Tổng độ phức tạp là O ((1+k)⋅m⋅n), với k là số lần lặp. Trong thực tế, k thường nhỏ hơn nhiều so với $$
2^n
$$, khiến phương pháp Simplex hiệu quả cho nhiều bài toán thực tế mặc dù hành vi tồi tệ nhất là lũy thừa.