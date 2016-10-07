//
//  arp.h
//  project3
//
//  Created by Kristen Kozmary on 10/4/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stddef.h>
#include <network.h>

#ifdef TRACE_ARP
#include <stdio.h>
#define ARP_TRACE(...) {\
        fprintf(TRACE_ARP, "%s:%d (%d) ", __FILE__, __LINE__, gettid()); \
        fprintf(TRACE_ARP, __VA_ARGS__); \
        fprintf(TRACE_ARP, "\n"); }
#else
#define ARP_TRACE(...)
#endif

#define ARP_HWTYPE_ETHERNET 1
#define ARP_PRTYPE_IPv4 ETHER_TYPE_IPv4

#define ARP_OP_RQST 1
#define ARP_OP_REPLY 2

#define ARP_CONST_HDR_LEN 6

#define ARP_NENTRY 32
#define ARP_FREE 0
#define ARP_USED 1
#define ARP_UNRESOLVED 1
#define ARP_RESOLVED 3
#define ARP_NTHRWAIT 10

#define ARP_MAX_LOOKUP 5
#define ARP_MSG_RESOLVED 1

#define ARP_TTL_UNRESOLVED 5
#define ARP_TTL_RESOLVED 300

#define ARP_THR_PRIO NET_THR_PRIO
#define ARP_THR_STK NET_THR_STK

#define ARP_ADDR_SHA(arp) 0
#define ARP_ADDR_SPA(arp) (arp->hwalen)
#define ARP_ADDR_DHA(arp) (arp->hwalen + arp->pralen)
#define ARP_ADDR_DPA(arp) ((2 * arp->hwalen) + arp->pralen)

#define ARP_NQUEUE 32

struct arpPkt {
  ushort hwtype;
  ushort prtype;
  uchar hwalen;
  uchar pralen;
  ushort op;
  uchar addrs[1];
};

struct arpEntry {
  ushort state;
  struct netif *nif;
  struct netaddr hwaddr;
  struct netaddr praddr;
  uint expires;
  tid_typ waiting[ARP_NTHRWAIT];
  int count;
};

extern struct arpEntry arptab[ARP_NENTRY];


struct arpEntry *arpAlloc(void);
thread arpDaemon(void);
struct arpEntry *arpGetEntry(struct netaddr *);
syscall arpFree(struct arpEntry *);
syscall arpInit(void);
syscall arpLookup(struct netif *, struct netaddr *, struct netaddr *);
syscall arpNotify(struct arpEntry *, message);
syscall arpRecv(struct packet *);
syscall arpSendRqst(struct arpEntry *);
syscall arpSendReply(struct packet *);
