#ifndef _H_SAMPLES_H_
#define _H_SAMPLES_H_

//////////////////////////////////////////////////////////////////////////
//IPV4->IPV6
//ӳ���� ����˵�� IPv4 IPv6
//�������� ��ַ�� AF_INET AF_INET6
//Э���� PF_INET PF_INET6
//IP��ַ�ṹ�� �ṹ�� sockaddr_in sockaddr_in6
//�ṹ���Ա:�׽ӿڳ��� sin_len sin6_len
//�ṹ���Ա:Э���� sin_family sin6_family
//�ṹ���Ա:�˿ں� sin_port sin6_port
//��ַ ͨ���ַ INADDR_ANY in6addr_any
//���ص�ַ INADDR_LOOPBACK in6addr_loopback
//��ַ�����ʽת������ �ַ�����ַתΪIP��ַ inet_aton() inet_pton()
//IP��ַ�ṹתΪ�ַ��� inet_ntoa() inet_ntop( )
//���֣���ַת������ �������ֻ��IP��ַ gethostbyname() getaddrinfo()
//����IP��ַ������� gethostbyaddr() getnameinfo()
//�������ֻ��IP��ַ gethostbyname2() getaddrinfo()
//���ݷ��������ȫ��������Ϣ getservbyname() getaddrinfo ()
//���ݷ���˿ڻ��ȫ��������Ϣ getservbyport() getaddrinfo()
//
//IPV6��ַfe80::21a:a5ff:fec1:1060%6������İٷֺ�6�ǽӿ�(�豸��ʶ��)����������windows����linux�˵Ļ�������ôping��ʱ�򣬾͵����ȼ���linux�˵�IPv6��ַ��Ȼ���ټ����Լ�windows�˵��豸�š�
//���磺
//linux����ipv6��ַ�� fe80::4e0f:6eff:fed8:489a/64
//windows����ipv6��ַ��fe80::21a:a5ff:fec1:1060%6
//��windows����ping��� ping fe80::4e0f:6eff:fed8:489a%6 ������Ŀ���ַ%���ؽӿڣ�

//#define USE_IPV6
#ifdef USE_IPV6
#define SockAddrType SOCKADDR_IN6
#else
#define SockAddrType SOCKADDR_IN
#endif//

//UDP�����ɿ����ݴ���
//Ҫʹ��UDP�������ɿ����������ӵ����ݴ��䣬��Ҫʵ��������TCPЭ��ĳ�ʱ�ش���������ܣ�Ӧ��ȷ�ϣ����������������ƵȻ��ƣ�
//����˵Ҫ�ڴ�������һ�㣨����ֱ����Ӧ�ò㣩ʵ��TCPЭ��Ŀɿ����ݴ�����ƣ�����ʹ��UDP���ݰ�+���кţ�UDP���ݰ�+ʱ����ȷ������ڷ������˽���Ӧ��ȷ�ϻ��ƣ�
//�����ͻᱣ֤���ɿ���UDPЭ����пɿ������ݴ��䡣
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
//1��IPV6�鲥��ַ
//	RFC4291�����鲥��ַ��ʽ���£�
//
//	|   8    |  4 |  4 |                     112                              |
//	+-------------------------------------------------------------------------+
//	|11111111|flgs|scop|                  group ID                            |
//	+-------------------------------------------------------------------------+
//
//
//	�鲥��ַ��8bitΪ�̶�ֵFF���˸�8��bit��4bitΪflgsλ��4bitΪ�鲥��ķ��鷶Χ��
//
//	flgsλΪ4bit�� |0|R|P|T|
//	flgsλ�ĸ�1bitΪ��������������Ϊ0
//	Tλ���Ϊ��0��ʾ���÷��������well-known�鲥��ַ�������1��ʾ��ʱ���䶯̬�ĵ�ַ�����̶���
//	Pλ�����1�Ļ���ʾ���鲥��ַ��һ�����ڵ���ǰ׺��ipv6�鲥��ַ��Ĭ��Ϊ0�����Pλ����Ϊ1����ôTλ����Ϊ1��
//	Rλ�����1�Ļ���ʾ���鲥��ַ��һ����ǶRP��ַ��ipv6�鲥��ַ��Ĭ��Ϊ0��
//
//	4bitscopeλ�������鲥��Ĵ�����Χ��
//
//	0  reserved
//	1  Interface-Local scope
//	2  Link-Local scope--��·���ط�Χ
//	3  reserved
//	4  Admin-Local scope-�����ط�Χ
//	5  Site-Local scope--վ�㱾�ط�Χ
//	6  (unassigned)
//	7  (unassigned)
//	8  Organization-Local scope-��֯���ط�Χ
//	9  (unassigned)
//	A  (unassigned)
//	B  (unassigned)
//	C  (unassigned)
//	D  (unassigned)
//	E  Global scope--ȫ�ַ�Χ��
//	F  reserved
//
//	��112bitΪ�鲥��ַ�Ŀ�����ID��
//
//	������link-local��Χ���鲥��ַ��������well-known��ַ��
//
//	���нڵ���鲥��ַ��  FF02:0:0:0:0:0:0:1
//	����·�������鲥��ַ��FF02:0:0:0:0:0:0:2 
//	Solicited-Node�鲥��ַ��  FF02:0:0:0:0:1:FFXX:XXXX
//	����OSPF·�����鲥��ַ�� FF02:0:0:0:0:0:0:5
//	����OSPF��DR·�����鲥��ַ�� FF02:0:0:0:0:0:0:6
//	����RIP·�����鲥��ַ�� FF02:0:0:0:0:0:0:9
//	����PIM·�����鲥��ַ�� FF02:0:0:0:0:0:0:D
//
//	ע��FF02��ͷ��FF�̶���ʽ��flgsλ��Ϊ0����ʾ���鲥��ַ����һ�����ڵ������鲥��ַҲ����һ����ǶRP���鲥��ַ������һ���̶���well-know���鲥��ַ��������ΧΪ����2 link-local��Χ��
//
//2��IPV6�鲥��ַ���¸�ʽ�����ڵ���ǰ׺���鲥��ַ��RFC3306��
//
//	|   8    |  4 |  4 |   8    |   8    |        64      |    32    |
//	+----------------------------------------------------------------+
//	|11111111|flgs|scop|reserved|  plen  | network prefix | group ID |
//	+----------------------------------------------------------------+
//
//	��8bitΪFF�̶�ֵ
//	4bit flgs��PΪ��Tλ����Ϊ1����ʾ���鲥��ַ��һ�����ڵ���ǰ׺���鲥��ַ��
//	scop�����Ʒ�Χͬ�ϡ�
//	8bit����λ������Ϊ0��
//	plenλ��8bit����ʾǰ׺�ľ��峤�ȡ��������Ϊ64��
//	Network prefixt����ʾ�����ǰ׺���ȡ�
//	Group id��32bit���鲥��ID��
//
//	����������������IPV6��ַ2002::2/64��ַ����ô���������淽���õ����鲥��ַΪ��
//	FF3X:0040:2002::Y(XΪ�鲥���Ƶķ�Χ��YΪ��ID��)�����ַ�������ʵ��ȫinternet���鲥��ַ�Ĳ���ͻ��ԭ������û�л���ȥ�����鲥��ַ��������IANA���䵥��ǰ׺������ͨ������ǰ׺���뵽�鲥��ַ�оͿ���ʵ�ֲ���ͻ��
//
//3��SSM��ַ��ʽ��RFC3306����
//	 ���ڵ���ǰ׺���鲥��ַҲ������SSM��ַ�ĸ�ʽ���̶�SSM��ַ��flagλ��P=1��plen=0��network prefix=0������SSM��ַ�ĸ�ʽ���£�
//
//	 |    8   |  4 |  4 |   8     |    8   |              64           |    32    |
//	 +----------------------------------------------------------------------------+
//	 |11111111|flgs|scop|reserved |     0  |         0                 | group ID |
//	 +----------------------------------------------------------------------------+
//	 �õ�SSM�鲥��ַ�ķ�ΧΪFF3X::/32��XΪ�鲥���Ƶķ�Χ��ÿ��SSM��ַ��ʽΪFF3X::/96��
//
//4����ǶRP��ַ��IPV6�鲥��ַ��
//	 ��ǶRP��ַ��IPV6�鲥��ַ�����鲥·�����յ������鲥������ݰ��Ϳ��Լ��������RP��ַ��
//
//	 | 20 bits | 4  | 8  |       64       |    32    |
//	 +-----------------------------------------------+
//	 |xtra bits|RIID|plen| network prefix | group ID |
//	 +-----------------------------------------------+
//
//	��8bit��FF
//	flgsλ��������Ϊ0111��Ҳ����R P Tbit������Ϊ1�����Ը�20bit�̶�ֵΪFF7X:00.
//	RIID,4bit RIID��ʾ����ǶRP��ipv6��ַ�ӿ�ID��
//	plen��8bit���ȣ���ʾ��RP��ַ��ǰ׺���ȡ�
//	Network prefix����ʾRP��ǰ׺��
//	��32bitΪ�鲥��ID��
//
//	����������һ��RP��ַΪ2022::2/64,��ô���������ԭ��õ���Ƕ��RP��ַ���鲥��ַΪ��
//	FF7X:0240:2022::Y(xΪ�鲥���Ʒ�Χ��yΪ�鲥ID)
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