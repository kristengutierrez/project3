//
//  arpFree.c
//  project3
//
//  Created by Kristen Kozmary on 10/5/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stddef.h>
#include "arp.h"
#include <interrupt.h>
#include <stdlib.h>

syscall arpFree(struct arpEntry *entry) {
  ARP_TRACE("Freeing ARP entry");
  
  if (NULL == entry) {
    return SYSERR;
  }
  
  if (ARP_UNRESOLVED == entry->state) {
    arpNotify(entry, TIMEOUT);
    ARP_TRACE("Waiting threads notified");
  }
  
  bzero(entry, sizeof(struct arpEntry));
  entry->state = ARP_FREE;
  ARP_TRACE("Freed entry %d", ((int)entry - (int)arptab) / sizeof(struct arpEntry));
  return 1;
}
