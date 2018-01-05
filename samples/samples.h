#ifndef _H_SAMPLES_H_
#define _H_SAMPLES_H_

//////////////////////////////////////////////////////////////////////////
//IPV4->IPV6
//映射项 功能说明 IPv4 IPv6
//常量定义 地址族 AF_INET AF_INET6
//协议族 PF_INET PF_INET6
//IP地址结构体 结构体 sockaddr_in sockaddr_in6
//结构体成员:套接口长度 sin_len sin6_len
//结构体成员:协议族 sin_family sin6_family
//结构体成员:端口号 sin_port sin6_port
//地址 通配地址 INADDR_ANY in6addr_any
//环回地址 INADDR_LOOPBACK in6addr_loopback
//地址－表达式转换函数 字符串地址转为IP地址 inet_aton() inet_pton()
//IP地址结构转为字符串 inet_ntoa() inet_ntop( )
//名字－地址转换函数 根据名字获得IP地址 gethostbyname() getaddrinfo()
//根据IP地址获得名字 gethostbyaddr() getnameinfo()
//根据名字获得IP地址 gethostbyname2() getaddrinfo()
//根据服务名获得全部服务信息 getservbyname() getaddrinfo ()
//根据服务端口获得全部服务信息 getservbyport() getaddrinfo()
//
//IPV6地址fe80::21a:a5ff:fec1:1060%6后面跟的百分号6是接口(设备标识符)。若是想用windows链接linux端的机器，那么ping的时候，就得首先加上linux端的IPv6地址，然后再加上自己windows端的设备号。
//例如：
//linux机器ipv6地址： fe80::4e0f:6eff:fed8:489a/64
//windows机器ipv6地址：fe80::21a:a5ff:fec1:1060%6
//在windows机器ping命令： ping fe80::4e0f:6eff:fed8:489a%6 （即：目标地址%本地接口）

//#define USE_IPV6
#ifdef USE_IPV6
#define SockAddrType SOCKADDR_IN6
#else
#define SockAddrType SOCKADDR_IN
#endif//

//UDP构建可靠数据传输
//要使用UDP来构建可靠的面向连接的数据传输，就要实现类似于TCP协议的超时重传，有序接受，应答确认，滑动窗口流量控制等机制，
//等于说要在传输层的上一层（或者直接在应用层）实现TCP协议的可靠数据传输机制，比如使用UDP数据包+序列号，UDP数据包+时间戳等方法，在服务器端进行应答确认机制，
//这样就会保证不可靠的UDP协议进行可靠的数据传输。
//#define USE_UDP
#define USE_MANAGER
#ifdef WIN32
#define USE_IOCP
#else
//#define USE_EPOLL
#ifdef USE_EPOLL
#define USE_EPOLLET
#endif//
#endif//

//#define DEFAULT_IP		"192.168.1.14"
#define DEFAULT_IP		"10.100.70.35"
//#define DEFAULT_IP		"127.0.0.1"
#define DEFAULT_PORT	6666
#define DEFAULT_BUFSIZE	1024

#ifdef USE_IPV6
//1、IPV6组播地址
//	RFC4291定义组播地址格式如下；
//
//	|   8    |  4 |  4 |                     112                              |
//	+-------------------------------------------------------------------------+
//	|11111111|flgs|scop|                  group ID                            |
//	+-------------------------------------------------------------------------+
//
//
//	组播地址高8bit为固定值FF，此高8个bit中4bit为flgs位，4bit为组播组的泛洪范围。
//
//	flgs位为4bit： |0|R|P|T|
//	flgs位的高1bit为保留，必须设置为0
//	T位如果为置0表示永久分配或者是well-known组播地址，如果置1表示临时分配动态的地址，不固定。
//	P位如果置1的话表示此组播地址是一个基于单播前缀的ipv6组播地址。默认为0，如果P位设置为1，那么T位必须为1。
//	R位如果置1的话表示此组播地址是一个内嵌RP地址的ipv6组播地址。默认为0。
//
//	4bitscope位来限制组播组的传播范围。
//
//	0  reserved
//	1  Interface-Local scope
//	2  Link-Local scope--链路本地范围
//	3  reserved
//	4  Admin-Local scope-管理本地范围
//	5  Site-Local scope--站点本地范围
//	6  (unassigned)
//	7  (unassigned)
//	8  Organization-Local scope-组织本地范围
//	9  (unassigned)
//	A  (unassigned)
//	B  (unassigned)
//	C  (unassigned)
//	D  (unassigned)
//	E  Global scope--全局范围的
//	F  reserved
//
//	低112bit为组播地址的可用组ID。
//
//	举例：link-local范围的组播地址，并且是well-known地址；
//
//	所有节点的组播地址：  FF02:0:0:0:0:0:0:1
//	所有路由器的组播地址：FF02:0:0:0:0:0:0:2 
//	Solicited-Node组播地址：  FF02:0:0:0:0:1:FFXX:XXXX
//	所有OSPF路由器组播地址： FF02:0:0:0:0:0:0:5
//	所有OSPF的DR路由器组播地址： FF02:0:0:0:0:0:0:6
//	所有RIP路由器组播地址： FF02:0:0:0:0:0:0:9
//	所有PIM路由器组播地址： FF02:0:0:0:0:0:0:D
//
//	注：FF02开头，FF固定格式，flgs位都为0，表示此组播地址不是一个基于单播的组播地址也不是一个内嵌RP的组播地址，而是一个固定的well-know的组播地址。传播范围为类型2 link-local范围。
//
//2、IPV6组播地址的新格式：基于单播前缀的组播地址（RFC3306）
//
//	|   8    |  4 |  4 |   8    |   8    |        64      |    32    |
//	+----------------------------------------------------------------+
//	|11111111|flgs|scop|reserved|  plen  | network prefix | group ID |
//	+----------------------------------------------------------------+
//
//	高8bit为FF固定值
//	4bit flgs，P为和T位必须为1，表示此组播地址是一个基于单播前缀的组播地址。
//	scop，限制范围同上。
//	8bit保留位，必须为0。
//	plen位，8bit。表示前缀的具体长度。（最长长度为64）
//	Network prefixt，表示具体的前缀长度。
//	Group id，32bit的组播组ID。
//
//	举例：比如现在有IPV6地址2002::2/64地址，那么它所用上面方法得到的组播地址为；
//	FF3X:0040:2002::Y(X为组播限制的范围，Y为组ID。)用这种方法可以实现全internet网组播地址的不冲突，原因在于没有机构去分配组播地址，但是由IANA分配单播前缀，这样通过单播前缀融入到组播地址中就可以实现不冲突。
//
//3、SSM地址格式：RFC3306定义
//	 基于单播前缀的组播地址也定义了SSM地址的格式；固定SSM地址的flag位里P=1，plen=0，network prefix=0、所以SSM地址的格式如下；
//
//	 |    8   |  4 |  4 |   8     |    8   |              64           |    32    |
//	 +----------------------------------------------------------------------------+
//	 |11111111|flgs|scop|reserved |     0  |         0                 | group ID |
//	 +----------------------------------------------------------------------------+
//	 得到SSM组播地址的范围为FF3X::/32，X为组播限制的范围。每个SSM地址格式为FF3X::/96。
//
//4、内嵌RP地址的IPV6组播地址；
//	 内嵌RP地址的IPV6组播地址，当组播路由器收到这样组播组的数据包就可以检测出该组的RP地址；
//
//	 | 20 bits | 4  | 8  |       64       |    32    |
//	 +-----------------------------------------------+
//	 |xtra bits|RIID|plen| network prefix | group ID |
//	 +-----------------------------------------------+
//
//	高8bit，FF
//	flgs位必须设置为0111。也就是R P Tbit都设置为1。所以高20bit固定值为FF7X:00.
//	RIID,4bit RIID表示此内嵌RP的ipv6地址接口ID。
//	plen，8bit长度，表示此RP地址的前缀长度。
//	Network prefix，表示RP的前缀。
//	低32bit为组播组ID。
//
//	举例：比如一个RP地址为2022::2/64,那么依据上面的原则得到内嵌此RP地址的组播地址为；
//	FF7X:0240:2022::Y(x为组播限制范围，y为组播ID)
#define DEFAULT_MULTICAST_IP	"FF02::99"
#define DEFAULT_MULTICAST_PORTS	"12345"
#else
#define DEFAULT_MULTICAST_IP	"224.0.0.255"
#endif//
#define DEFAULT_MULTICAST_PORT	12345

#define DEFAULT_CLIENT_COUNT 5
 
#ifdef USE_EPOLL
#define DEFAULT_FD_SETSIZE 200
#else
#define DEFAULT_FD_SETSIZE 16
#endif//
#define DEFAULT_MAX_FD_SETSIZE 20000

#endif//_H_SAMPLES_H_