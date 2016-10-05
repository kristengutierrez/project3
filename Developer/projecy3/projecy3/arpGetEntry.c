//
//  arpGetEntry.c
//  project3
//
//  Created by Kristen Kozmary on 10/5/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stddef.h>
#include "arp.h"
#include <clock.h>
#include <interrupt.h>

struct arpEntry *arpGetEntry(struct netaddr *praddr) {
  int i = 0;
  struct arpEntry *entry = NULL;
  irqmask im;
  ARP_TRACE("Getting ARP entry");
  im = disable();
  
  for (i = 0; i < ARP_NENTRY; i++) {
    if (!(ARP_USED & arptab[i].state)) {
      continue;
    }
    
    entry = &arptab[i];
    if (entry->expires <clktime) {
      ARP_TRACE("\tEntry %d expired", i);
      arpFree(entry);
      continue;
    }
    
    if (netaddrequal(&entry->praddr, praddr)) {
      restore(im);
      ARP_TRACE("\tEntry %d matches", i);
      return entry;
    }
  }
  
  restore(im);
  ARP_TRACE("\tNo entry matches");
  return NULL;
}
