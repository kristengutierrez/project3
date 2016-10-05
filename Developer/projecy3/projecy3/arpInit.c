//
//  arpInit.c
//  project3
//
//  Created by Kristen Kozmary on 10/5/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stdlib.h>
#include <stddef.h>
#include "arp.h"
#include <mailbox.h>
#include <thread.h>

struct arpEntry arptab[ARP_NENTRY];
mailbox arpqueue;

syscall arpInit(void) {
  int i = 0;
  
  for (i = 0; i < ARP_NENTRY; i++) {
    bzero(&arptab[i], sizeof(struct arpEntry));
    arptab[i].state = ARP_FREE;
  }
  
  arpqueue = mailboxAlloc(ARP_NQUEUE);
  if (SYSERR == arpqueue) {
    return SYSERR;
  }
  
  ready(create ((void *) arpDaemon, ARP_THR_STK, ARP_THR_PRIO, "arpDaemon", 0), RESCHED_NO);
  
  return 1;
}
