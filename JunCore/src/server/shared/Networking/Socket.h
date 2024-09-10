 #include <boost/asio/ip/tcp.hpp>

template<class T, class Stream = boost::asio::ip::tcp::socket>
class Socket : public std::enable_shared_from_this<T>
{
public:
	int f() {
		return 33;
	}
};