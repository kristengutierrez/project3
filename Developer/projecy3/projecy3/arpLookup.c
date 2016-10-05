//
//  arpLookup.c
//  project3
//
//  Created by Kristen Kozmary on 10/5/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stddef.h>
#include "arp.h"
#include <clock.h>
#include <interrupt.h>
#include <string.h>
#include <thread.h>

syscall arpLookup(struct netif *netptr, struct netaddr *praddr, struct netaddr *hwaddr) {
  
  struct arpEntry *entry = NULL;
  uint lookups = 0;
  int ttl;
  irqmask im;
  
  if ((NULL == netptr) || (NULL == praddr) || (NULL == hwaddr)) {
    ARP_TRACE("Invalid args");
    return SYSERR;
  }
  
  ARP_TRACE("Looking up protocol address");
  
  while (lookups < ARP_MAX_LOOKUP) {
    lookups++;
    
    im = disable();
    entry = arpGetEntry(praddr);
    
    if (NULL == entry) {
      ARP_TRACE("Entry doesn't exist");
      entry = arpAlloc();
      if (SYSERR == (int)entry) {
        restore(im);
        return SYSERR;
      }
      
      entry->state = ARP_UNRESOLVED;
      entry->nif = netptr;
      netaddrcpy(&entry->praddr, praddr);
      entry->expires = clktime + ARP_TTL_UNRESOLVED;
      entry->count = 0;
    }
    
    if (ARP_RESOLVED == entry->state) {
      netraddrcpy(hwaddr, &entry->hwaddr);
      ARP_TRACE("Entry exists");
      return OK;
    }
    
    if (entry->count >= ARP_NTHRWAIT) {
      restore(im);
      ARP_TRACE("Queue of waiting threads is full");
      return SYSERR;
    }
    
    entry->waiting[entry->count] = gettid();
    entry->count++;
    ttl = (entry->expires - clktime) * CLKTICKS_PER_SEC;
    restore(im);
    
    if (SYSERR == arpSendRqst(entry)) {
      ARP_TRACE("Failed to send request");
      return SYSERR;
    }
    
    recvclr();
    switch (recvtime(ttl)) {
      case TIMEOUT:
      case SYSERR:
        return SYSERR;
      case ARP_MSG_RESOLVED:
      default:
        continue;
    }
  }
  return SYSERR;
}
