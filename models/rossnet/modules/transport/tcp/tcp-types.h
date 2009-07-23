#ifndef INC_tcp_types_h
#define INC_tcp_types_h

#define	TW_TCP_HOST   1

#define TCP_SND_WND  65536
//#define TCP_SND_WND  66048
#define TCP_HEADER_SIZE 40.0
//#define TCP_HEADER_SIZE 36.0
#define TCP_MTU (state->mss + TCP_HEADER_SIZE)

FWD(struct, tcp_state);
FWD(struct, RC);
FWD(struct, tcp_message);
FWD(enum, tcp_event_t);
FWD(struct, tcp_statistics);

DEF(struct, tcp_state)
{
	//rn_machine	*host;

	int             unack;
	int             seq_num;
	int             dup_count;
	int             len;
	int             timeout;
	int             rtt_seq;
	char 		out_of_order[33];
	int             rto_seq;
	int		mss;
	int		recv_wnd;

	tw_lpid		connection;

	tw_event        *timer;

#ifdef CLIENT_DROP
	int             count;
#endif

	tw_stime	lastsent;
	tw_stime	cwnd;
	tw_stime	ssthresh;
	tw_stime	rtt_time;
	tw_stime	rto;

	tcp_statistics	*stats;

#if TCP_LOG
	FILE		*log;
#endif
};

DEF(struct, RC)
{
	tw_stime	dup_count;
	tw_stime	cwnd;
	tw_stime	rtt_time;
	tw_stime	lastsent;
	tw_stime	rto;
	tw_stime	ssthresh;

	char		out_of_order[33];

	tw_event        *timer;
	tw_stime        timer_ts;
	int             timer_seq;

	int             rtt_seq;
	int             seq_num;
	int		unack;
	int		sent;
};

DEF(enum, tcp_event_t)
{
	TCP_CLIENT = 1,
	TCP_SERVER,
	TCP_CONNECT
};

DEF(struct, tcp_message)
{
	//tcp_event_t	type;
	int             ack;
	int             seq_num;
	tw_lpid		src;

	RC              RC;
};

DEF(struct, tcp_statistics)
{
	int		bad_msgs;
	int             sent;
	int             tout;
	int             recv;
	int             dropped_packets;

	tw_stime	throughput;
	tw_stime	start_time;
	tw_stime	final_time;

	int		ack_invalid;
	int		ack_sent;
	int		ack_recv;
};

#endif
