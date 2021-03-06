/*
 * Copyright (c) 2016, Imagination Technologies Limited and/or its affiliated
 * group companies.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file
 * 	 codes to get proximity data when exceed High thershold.
 *
 */

#include <contiki.h>
#include <stdio.h>
#include <lib/sensors.h>
#include "dev/common-clicks.h"
#include "dev/leds.h"
#include "sys/clock.h"
/*---------------------------------------------------------------------------*/
PROCESS(test_proximity, "testing proximity-click");
AUTOSTART_PROCESSES(&test_proximity);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(test_proximity, ev, data)
{
  static int i;
  static int val;
  PROCESS_EXITHANDLER(goto exit;)
  PROCESS_BEGIN();
  SENSORS_ACTIVATE(proximity_sensor);

  while(1) {
  PROCESS_WAIT_EVENT_UNTIL((ev == sensors_event));
  val = proximity_sensor.value(0);
  printf("Proximity value = %d \n",val);

  if(data == &proximity_sensor) {
      printf("Obstacle detected by sensor\n");
      leds_on(LEDS_ALL);
      /*  Delay for 500ms */
      for(i=0;i<=500;++i) {
        clock_delay_usec(1000);
      }
      leds_off(LEDS_ALL);
    }
  }

  exit:
  SENSORS_DEACTIVATE(proximity_sensor);
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
