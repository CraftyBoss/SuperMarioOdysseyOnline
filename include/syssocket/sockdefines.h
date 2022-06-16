/*
 * User-settable options (used with setsockopt).
 */
#define	TCP_NODELAY		 1  /* Don't delay send to coalesce packets  */
#define	TCP_MAXSEG		 2  /* Set maximum segment size  */
#define TCP_CORK		 3  /* Control sending of partial frames  */
#define TCP_KEEPIDLE		 4  /* Start keeplives after this period */
#define TCP_KEEPINTVL		 5  /* Interval between keepalives */
#define TCP_KEEPCNT		 6  /* Number of keepalives before death */
#define TCP_SYNCNT		 7  /* Number of SYN retransmits */
#define TCP_LINGER2		 8  /* Life time of orphaned FIN-WAIT-2 state */
#define TCP_DEFER_ACCEPT	 9  /* Wake up listener only when data arrive */
#define TCP_WINDOW_CLAMP	 10 /* Bound advertised window */
#define TCP_INFO		 11 /* Information about this connection. */
#define	TCP_QUICKACK		 12 /* Bock/reenable quick ACKs.  */
#define TCP_CONGESTION		 13 /* Congestion control algorithm.  */
#define TCP_MD5SIG		 14 /* TCP MD5 Signature (RFC2385) */
#define TCP_COOKIE_TRANSACTIONS	 15 /* TCP Cookie Transactions */
#define TCP_THIN_LINEAR_TIMEOUTS 16 /* Use linear timeouts for thin streams*/
#define TCP_THIN_DUPACK		 17 /* Fast retrans. after 1 dupack */
#define TCP_USER_TIMEOUT	 18 /* How long for loss retry before timeout */
#define TCP_REPAIR		 19 /* TCP sock is under repair right now */
#define TCP_REPAIR_QUEUE	 20 /* Set TCP queue to repair */
#define TCP_QUEUE_SEQ		 21 /* Set sequence number of repaired queue. */
#define TCP_REPAIR_OPTIONS	 22 /* Repair TCP connection options */
#define TCP_FASTOPEN		 23 /* Enable FastOpen on listeners */
#define TCP_TIMESTAMP		 24 /* TCP time stamp */
#define TCP_NOTSENT_LOWAT	 25 /* Limit number of unsent bytes in
				       write queue.  */
#define TCP_CC_INFO		 26 /* Get Congestion Control
				       (optional) info.  */
#define TCP_SAVE_SYN		 27 /* Record SYN headers for new
				       connections.  */
#define TCP_SAVED_SYN		 28 /* Get SYN headers recorded for
				       connection.  */
#define TCP_REPAIR_WINDOW	 29 /* Get/set window parameters.  */
#define TCP_FASTOPEN_CONNECT	 30 /* Attempt FastOpen with connect.  */
#define TCP_ULP			 31 /* Attach a ULP to a TCP connection.  */
#define TCP_MD5SIG_EXT		 32 /* TCP MD5 Signature with extensions.  */
#define TCP_FASTOPEN_KEY	 33 /* Set the key for Fast Open (cookie).  */
#define TCP_FASTOPEN_NO_COOKIE	 34 /* Enable TFO without a TFO cookie.  */
#define TCP_ZEROCOPY_RECEIVE	 35
#define TCP_INQ			 36 /* Notify bytes available to read
				       as a cmsg on read.  */
#define TCP_CM_INQ		 TCP_INQ
#define TCP_TX_DELAY		 37 /* Delay outgoing packets by XX usec.  */

#define TCP_REPAIR_ON		 1
#define TCP_REPAIR_OFF		 0
#define TCP_REPAIR_OFF_NO_WP	 -1
/*
 * Types
 */
#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_RAW	3		/* raw-protocol interface */
#if __BSD_VISIBLE
#define	SOCK_RDM	4		/* reliably-delivered message */
#endif
#define	SOCK_SEQPACKET	5		/* sequenced packet stream */

#if __BSD_VISIBLE
/*
 * Creation flags, OR'ed into socket() and socketpair() type argument.
 */
#define	SOCK_CLOEXEC	0x10000000
#define	SOCK_NONBLOCK	0x20000000

#endif	/* __BSD_VISIBLE */

/*
 * Option flags per-socket.
 */
#define	SO_DEBUG	0x0001		/* turn on debugging info recording */
#define	SO_ACCEPTCONN	0x0002		/* socket has had listen() */
#define	SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	SO_KEEPALIVE	0x0008		/* keep connections alive */
#define	SO_DONTROUTE	0x0010		/* just use interface addresses */
#define	SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
#if __BSD_VISIBLE
#define	SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
#endif
#define	SO_LINGER	0x0080		/* linger on close if data present */
#define	SO_OOBINLINE	0x0100		/* leave received OOB data in line */
#if __BSD_VISIBLE
#define	SO_REUSEPORT	0x0200		/* allow local address & port reuse */
#define	SO_TIMESTAMP	0x0400		/* timestamp received dgram traffic */
#define	SO_NOSIGPIPE	0x0800		/* no SIGPIPE from EPIPE */
#define	SO_ACCEPTFILTER	0x1000		/* there is an accept filter */
#define	SO_BINTIME	0x2000		/* timestamp received dgram traffic */
#endif
#define	SO_NO_OFFLOAD	0x4000		/* socket cannot be offloaded */
#define	SO_NO_DDP	0x8000		/* disable direct data placement */

/*
 * Additional options, not kept in so_options.
 */
#define	SO_SNDBUF	0x1001		/* send buffer size */
#define	SO_RCVBUF	0x1002		/* receive buffer size */
#define	SO_SNDLOWAT	0x1003		/* send low-water mark */
#define	SO_RCVLOWAT	0x1004		/* receive low-water mark */
#define	SO_SNDTIMEO	0x1005		/* send timeout */
#define	SO_RCVTIMEO	0x1006		/* receive timeout */
#define	SO_ERROR	0x1007		/* get error status and clear */
#define	SO_TYPE		0x1008		/* get socket type */
#if __BSD_VISIBLE
#define	SO_LABEL	0x1009		/* socket's MAC label */
#define	SO_PEERLABEL	0x1010		/* socket's peer's MAC label */
#define	SO_LISTENQLIMIT	0x1011		/* socket's backlog limit */
#define	SO_LISTENQLEN	0x1012		/* socket's complete queue length */
#define	SO_LISTENINCQLEN	0x1013	/* socket's incomplete queue length */
#define	SO_SETFIB	0x1014		/* use this FIB to route */
#define	SO_USER_COOKIE	0x1015		/* user cookie (dummynet etc.) */
#define	SO_PROTOCOL	0x1016		/* get socket protocol (Linux name) */
#define	SO_PROTOTYPE	SO_PROTOCOL	/* alias for SO_PROTOCOL (SunOS name) */
#define	SO_TS_CLOCK	0x1017		/* clock type used for SO_TIMESTAMP */
#define	SO_MAX_PACING_RATE	0x1018	/* socket's max TX pacing rate (Linux name) */
#endif

#if __BSD_VISIBLE
#define	SO_TS_REALTIME_MICRO	0	/* microsecond resolution, realtime */
#define	SO_TS_BINTIME		1	/* sub-nanosecond resolution, realtime */
#define	SO_TS_REALTIME		2	/* nanosecond resolution, realtime */
#define	SO_TS_MONOTONIC		3	/* nanosecond resolution, monotonic */
#define	SO_TS_DEFAULT		SO_TS_REALTIME_MICRO
#define	SO_TS_CLOCK_MAX		SO_TS_MONOTONIC
#endif

/*
 * Space reserved for new socket options added by third-party vendors.
 * This range applies to all socket option levels.  New socket options
 * in FreeBSD should always use an option value less than SO_VENDOR.
 */
#if __BSD_VISIBLE
#define	SO_VENDOR	0x80000000
#endif

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	SOL_SOCKET	0xffff		/* options for socket level */

/*
 * Address families.
 */
#define	AF_UNSPEC	0		/* unspecified */
#if __BSD_VISIBLE
#define	AF_LOCAL	AF_UNIX		/* local to host (pipes, portals) */
#endif
#define	AF_UNIX		1		/* standardized name for AF_LOCAL */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#if __BSD_VISIBLE
#define	AF_IMPLINK	3		/* arpanet imp addresses */
#define	AF_PUP		4		/* pup protocols: e.g. BSP */
#define	AF_CHAOS	5		/* mit CHAOS protocols */
#define	AF_NETBIOS	6		/* SMB protocols */
#define	AF_ISO		7		/* ISO protocols */
#define	AF_OSI		AF_ISO
#define	AF_ECMA		8		/* European computer manufacturers */
#define	AF_DATAKIT	9		/* datakit protocols */
#define	AF_CCITT	10		/* CCITT protocols, X.25 etc */
#define	AF_SNA		11		/* IBM SNA */
#define AF_DECnet	12		/* DECnet */
#define AF_DLI		13		/* DEC Direct data link interface */
#define AF_LAT		14		/* LAT */
#define	AF_HYLINK	15		/* NSC Hyperchannel */
#define	AF_APPLETALK	16		/* Apple Talk */
#define	AF_ROUTE	17		/* Internal Routing Protocol */
#define	AF_LINK		18		/* Link layer interface */
#define	pseudo_AF_XTP	19		/* eXpress Transfer Protocol (no AF) */
#define	AF_COIP		20		/* connection-oriented IP, aka ST II */
#define	AF_CNT		21		/* Computer Network Technology */
#define pseudo_AF_RTIP	22		/* Help Identify RTIP packets */
#define	AF_IPX		23		/* Novell Internet Protocol */
#define	AF_SIP		24		/* Simple Internet Protocol */
#define	pseudo_AF_PIP	25		/* Help Identify PIP packets */
#define	AF_ISDN		26		/* Integrated Services Digital Network*/
#define	AF_E164		AF_ISDN		/* CCITT E.164 recommendation */
#define	pseudo_AF_KEY	27		/* Internal key-management function */
#endif
#define	AF_INET6	28		/* IPv6 */
#if __BSD_VISIBLE
#define	AF_NATM		29		/* native ATM access */
#define	AF_ATM		30		/* ATM */
#define pseudo_AF_HDRCMPLT 31		/* Used by BPF to not rewrite headers
					 * in interface output routine
					 */
#define	AF_NETGRAPH	32		/* Netgraph sockets */
#define	AF_SLOW		33		/* 802.3ad slow protocol */
#define	AF_SCLUSTER	34		/* Sitara cluster protocol */
#define	AF_ARP		35
#define	AF_BLUETOOTH	36		/* Bluetooth sockets */
#define	AF_IEEE80211	37		/* IEEE 802.11 protocol */
#define	AF_INET_SDP	40		/* OFED Socket Direct Protocol ipv4 */
#define	AF_INET6_SDP	42		/* OFED Socket Direct Protocol ipv6 */
#define	AF_MAX		42
/*
 * When allocating a new AF_ constant, please only allocate
 * even numbered constants for FreeBSD until 134 as odd numbered AF_
 * constants 39-133 are now reserved for vendors.
 */
#define AF_VENDOR00 39
#define AF_VENDOR01 41
#define AF_VENDOR02 43
#define AF_VENDOR03 45
#define AF_VENDOR04 47
#define AF_VENDOR05 49
#define AF_VENDOR06 51
#define AF_VENDOR07 53
#define AF_VENDOR08 55
#define AF_VENDOR09 57
#define AF_VENDOR10 59
#define AF_VENDOR11 61
#define AF_VENDOR12 63
#define AF_VENDOR13 65
#define AF_VENDOR14 67
#define AF_VENDOR15 69
#define AF_VENDOR16 71
#define AF_VENDOR17 73
#define AF_VENDOR18 75
#define AF_VENDOR19 77
#define AF_VENDOR20 79
#define AF_VENDOR21 81
#define AF_VENDOR22 83
#define AF_VENDOR23 85
#define AF_VENDOR24 87
#define AF_VENDOR25 89
#define AF_VENDOR26 91
#define AF_VENDOR27 93
#define AF_VENDOR28 95
#define AF_VENDOR29 97
#define AF_VENDOR30 99
#define AF_VENDOR31 101
#define AF_VENDOR32 103
#define AF_VENDOR33 105
#define AF_VENDOR34 107
#define AF_VENDOR35 109
#define AF_VENDOR36 111
#define AF_VENDOR37 113
#define AF_VENDOR38 115
#define AF_VENDOR39 117
#define AF_VENDOR40 119
#define AF_VENDOR41 121
#define AF_VENDOR42 123
#define AF_VENDOR43 125
#define AF_VENDOR44 127
#define AF_VENDOR45 129
#define AF_VENDOR46 131
#define AF_VENDOR47 133
#endif

#define	MSG_OOB		 0x00000001	/* process out-of-band data */
#define	MSG_PEEK	 0x00000002	/* peek at incoming message */
#define	MSG_DONTROUTE	 0x00000004	/* send without using routing tables */
#define	MSG_EOR		 0x00000008	/* data completes record */
#define	MSG_TRUNC	 0x00000010	/* data discarded before delivery */
#define	MSG_CTRUNC	 0x00000020	/* control data lost before delivery */
#define	MSG_WAITALL	 0x00000040	/* wait for full request or error */
#define	MSG_DONTWAIT	 0x00000080	/* this message should be nonblocking */
#if __BSD_VISIBLE
#define	MSG_EOF		 0x00000100	/* data completes connection */
/*			 0x00000200	   unused */
/*			 0x00000400	   unused */
/*			 0x00000800	   unused */
/*			 0x00001000	   unused */
#define	MSG_NOTIFICATION 0x00002000	/* SCTP notification */
#define	MSG_NBIO	 0x00004000	/* FIONBIO mode, used by fifofs */
#define	MSG_COMPAT       0x00008000		/* used in sendit() */
#endif
#if __POSIX_VISIBLE >= 200809
#define	MSG_NOSIGNAL	 0x00020000	/* do not generate SIGPIPE on EOF */
#endif
#if __BSD_VISIBLE
#define	MSG_CMSG_CLOEXEC 0x00040000	/* make received fds close-on-exec */
#define	MSG_WAITFORONE	 0x00080000	/* for recvmmsg() */
#endif