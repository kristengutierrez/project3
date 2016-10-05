//
//  arpAlloc.c
//  project3
//
//  Created by Kristen Kozmary on 10/5/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stdlib.h>
#include "arp.h"
#include <stddef.h>

struct arpEntry *arpAlloc(void) {
  struct arpEntry *minexpires = NULL;
  int i = 0;
  
  ARP_TRACE("Allocating ARP entry");
  
  for (i = 0; i < ARP_NENTRY; i++) {
    if (ARP_FREE == arptab[i].state) {
      arptab[i].state = ARP_USED;
      ARP_TRACE("\tFree entry %d", i);
      return &arptab[i];
    }
    
    if ((NULL == minexpires) || (arptab[i].expires < minexpires->expires)) {
      minexpires = &arptab[i];
      ARP_TRACE("\tMinexpires entry %d, expires %u", i, minexpires->expires);
    }
  }
  
  if (NULL == minexpires) {
    ARP_TRACE("\tNo free or minexpires entry");
    return (struct arpEntry *)SYSERR;
  }
  
  bzero(minexpires, sizeof(struct arpEntry));
  minexpires->state = ARP_USED;
  return minexpires;
}
