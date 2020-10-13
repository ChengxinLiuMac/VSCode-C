
/*
 * 
 * Simulation_Run of A Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/******************************************************************************/

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/******************************************************************************/

/*
 * This function outputs a progress message to the screen to indicate this are
 * working.
 */

void
output_progress_msg_to_screen(Simulation_Run_Ptr simulation_run)
{
  double percentage_done;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter++;

  if((data->blip_counter >= BLIPRATE)
     ||
     (data->number_of_packets_processed1 + data->number_of_packets_processed2 + data->number_of_packets_processed3 >= RUNLENGTH)) {

    data->blip_counter = 0;

    percentage_done =
      100 * (double)(data->number_of_packets_processed1 + data->number_of_packets_processed2 + data->number_of_packets_processed3 )/RUNLENGTH;

    printf("%3.0f%% ", percentage_done);

    printf("Link 1 successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \r", 
	    data->number_of_packets_processed1, data->arrival_count1);
    fflush(stdout);
    printf("Link 2 successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \r",
        data->number_of_packets_processed2, data->arrival_count2);
    fflush(stdout);
    printf("Link 3 successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \r",
        data->number_of_packets_processed3, data->arrival_count3);
    fflush(stdout);
  }

}

/*
 * When a simulation_run run is completed, this function outputs various
 * collected statistics on the screen.
 */

void
output_results(Simulation_Run_Ptr simulation_run)
{
  double xmtted_fraction1, xmtted_fraction2, xmtted_fraction3;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  printf("\n");
  printf("Random Seed = %d \n", data->random_seed);
  printf("p12 = %f \n", data->p12);
  printf("Link 1 packet arrival count = %ld \n", data->arrival_count1);
  printf("Link 2 packet arrival count = %ld \n", data->arrival_count2);
  printf("Link 3 packet arrival count = %ld \n", data->arrival_count3);

  xmtted_fraction1 = (double)data->number_of_packets_processed1 /
      data->arrival_count1;  
  xmtted_fraction2 = (double)data->number_of_packets_processed2 /
      data->arrival_count2;  
  xmtted_fraction3 = (double)data->number_of_packets_processed3 /
      data->arrival_count3;

  printf("Link 1 transmitted packet count  = %ld (Service Fraction = %.5f)\n",
	  data->number_of_packets_processed1, xmtted_fraction1);
  printf("Link 2 transmitted packet count  = %ld (Service Fraction = %.5f)\n",
      data->number_of_packets_processed2, xmtted_fraction2);
  printf("Link 3 transmitted packet count  = %ld (Service Fraction = %.5f)\n",
      data->number_of_packets_processed3, xmtted_fraction3);

  printf("Link 1 arrival rate = %ld packets/second \n", data->arrival_rate1);
  printf("Link 2 arrival rate = %ld packets/second \n", data->arrival_rate2);
  printf("Link 3 arrival rate = %ld packets/second \n", data->arrival_rate3);

  printf("Link 1 mean Delay (msec) = %.2f \n",
      1e3 * data->accumulated_delay1 / data->number_of_packets_processed1);
  printf("Link 2 mean Delay (msec) = %.2f \n",
      1e3 * data->accumulated_delay2 / data->number_of_packets_processed2);
  printf("Link 3 mean Delay (msec) = %.2f \n",
      1e3 * data->accumulated_delay3 / data->number_of_packets_processed3);

  printf("\n");
}



