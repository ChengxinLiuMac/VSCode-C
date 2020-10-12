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

/*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "output.h"
#include "simparameters.h"
#include "packet_arrival.h"
#include "cleanup_memory.h"
#include "trace.h"
#include "main.h"

/******************************************************************************/

/*
 * main.c declares and creates a new simulation_run with parameters defined in
 * simparameters.h. The code creates a fifo queue and server for the single
 * server queueuing system. It then loops through the list of random number
 * generator seeds defined in simparameters.h, doing a separate simulation_run
 * run for each. To start a run, it schedules the first packet arrival
 * event. When each run is finished, output is printed on the terminal.
 */

int main()
{
  Simulation_Run_Ptr simulation_run;
  Simulation_Run_Ptr simulation_run2;
  Simulation_Run_Ptr simulation_run3;
  Simulation_Run_Data data;
  Simulation_Run_Data data2;
  Simulation_Run_Data data3;


  /*
   * Declare and initialize our random number generator seeds defined in
   * simparameters.h
   */

  unsigned RANDOM_SEEDS[] = {RANDOM_SEED_LIST, 0};
  unsigned random_seed;

  /* 
   * Loop for each random number generator seed, doing a separate
   * simulation_run run for each.
   */
  

	for (double p12 = 0; p12 < 1; p12+=0.1) {
	  int j = 0;
		while ((random_seed = RANDOM_SEEDS[j++]) != 0) 
	  	{

			simulation_run = simulation_run_new(); /* Create a new simulation run. */
			simulation_run2 = simulation_run_new(); /* Create a new simulation run. */
			simulation_run3 = simulation_run_new(); /* Create a new simulation run. */

		  /*
		   * Set the simulation_run data pointer to our data object.
		   */

		  simulation_run_attach_data(simulation_run, (void *)& data);
		  simulation_run_attach_data(simulation_run2, (void *)& data2);
		  /*
		   * Initialize the simulation_run data variables, declared in main.h.
		   */

			data.blip_counter = 0;
			data.arrival_count = 0;
      		// data.over20_packet_count = 0;
      		data.number_of_packets_processed = 0;
      		data.accumulated_delay = 0.0;
			data.arrival_rate = 750;
			data.random_seed = random_seed;

      		data2.blip_counter = 0;
			data2.arrival_count = 0;
      		// data2.over20_packet_count = 0;
      		data2.number_of_packets_processed = 0;
      		data2.accumulated_delay = 0.0;
			data2.arrival_rate = 500;
			data2.random_seed = random_seed;

      		data3.blip_counter = 0;
			data3.arrival_count = 0;
      		// data3.over20_packet_count = 0;
      		data3.number_of_packets_processed = 0;
      		data3.accumulated_delay = 0.0;
			data3.arrival_rate = 500;
			data3.random_seed = random_seed;

			printf("current data1 rate is %d \n" , data.arrival_rate);
      		printf("current data2 rate is %d \n" , data2.arrival_rate);
      		printf("current data3 rate is %d \n" , data3.arrival_rate);

		  /*
		   * Create the packet buffer and transmission link, declared in main.h.
		   */

			data.buffer = fifoqueue_new();
			data.link = server_new();
      		data2.buffer = fifoqueue_new();
			data2.link = server_new();
      		data3.buffer = fifoqueue_new();
			data3.link = server_new();

		  /*
		   * Set the random number generator seed for this run.
		   */

			random_generator_initialize(random_seed);

		  /*
		   * Schedule the initial packet arrival for the current clock time (= 0).
		   */

			schedule_packet_arrival_event(simulation_run, simulation_run2, simulation_run_get_time(simulation_run));

		  /*
		   * Execute events until we are finished.
		   */
      		while (data2.number_of_packets_processed < RUNLENGTH)
      		{
				while (data.number_of_packets_processed < RUNLENGTH)
				{
					simulation_run_execute_event(simulation_run);
				}
				simulation_run_execute_event(simulation_run2);
			}

		  /*
		   * Output results and clean up after ourselves.
		   */

			output_results(simulation_run);
			cleanup_memory(simulation_run);
  		}
	}
	getchar();   /* Pause before finishing. */
  	return 0;
}