//
//  arpDaemon.c
//  project3
//
//  Created by Kristen Kozmary on 10/5/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stddef.h>
#include "arp.h"
#include <mailbox.h>

thread arpDaemon(void) {
  struct packet *pkt = NULL;
  
  while (TRUE) {
    pkt = (struct packet *)mailboxReceive(arpqueue);
    ARP_TRACE("Daemon received ARP packet");
    if(SYSERR == (int)pkt) {
      continue;
    }
    arpSendReply(pkt);
    
    if (SYSERR == netFreebuf(pkt)) {
      ARP_TRACE("Failed to free packet buffer");
      continue;
    }
  }
  return 1;
}
