#include <Define.h>
#include <vector>
#include <queue>
#include <atomic>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

struct MessageBuffer
{
	using storage	= std::vector<uint8>;
	using size_type = std::vector<uint8>::size_type;

public:
	MessageBuffer() : _wpos(0), _rpos(0), _storage()
	{
		_storage.resize(4096);
	}

private:
	size_type _wpos;
	size_type _rpos;
	storage _storage;
};

template<class T>
class Socket : public std::enable_shared_from_this<T>
{
public:
	explicit Socket(tcp::socket&& socket)
		: _socket(std::move(socket)), _remoteAddress(_socket.remote_endpoint().address()), _remotePort(_socket.remote_endpoint().port()), _readBuffer(), _closed(false), _closing(false), _isWritingAsync(false)
	{
		_readBuffer.Resize(READ_BLOCK_SIZE);
	}

private:
	tcp::socket _socket;

	boost::asio::ip::address _remoteAddress;
	uint16 _remotePort;

	MessageBuffer _readBuffer;
	std::queue<MessageBuffer> _writeQueue;

	std::atomic<bool> _closed;
	std::atomic<bool> _closing;

	bool _isWritingAsync;
};