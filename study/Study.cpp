/*
 * Study.cpp
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#include <string>

#include "Study.h"
#include "../generator/Generator.h"
#include "../simulator/TaskFileParser.h"
#include "../simulator/Simulator.h"

#define H_UTILIZATION 80
#define L_UTILIZATION 40
#define H_MEMORY 6
#define L_MEMORY 3
#define H_NBTASKS 6
#define L_NBTASKS 3
#define RAM_SIZE 9
#define LOAD_TIME 2

#define REPEAT 1000

void Study::init() {
	Generator::init();
}

Study::Study() {}

void Study::run(int utilization, int memory, int nbTasks, std::string fileName, std::string name) {
	int simFail = 0, audsleyFail = 0;
	int preemption = 0, idleTime = 0, swapTime = 0, swapCpt = 0, simLength = 0;
	float ut = 0, sysLoad = 0;

	for (int i=0;i<REPEAT;++i) {
		Generator g1(utilization,memory,nbTasks,fileName);
		g1.generate(); g1.toFile();
		TaskFileParser parser(fileName);
		std::vector<Task> tasks = parser.parse();
		Simulator s(tasks, RAM_SIZE, LOAD_TIME);

		int status = s.simulate(false);
		if (status==1) ++audsleyFail;
		else if (status==2) ++simFail;
		else {
			preemption+=s.getPreemptionCpt();
			idleTime+=s.getIdleTime();
			swapTime+=s.getSwapTime();
			ut+=s.getUtilization();
			swapCpt+=s.getSwapCpt();
			sysLoad+=s.getSysLoad();
			simLength+=s.getSimLength();
		}
	}
	std::cout << "~" << name << "~" << std::endl;
	std::cout << "Total : " << REPEAT << std::endl;
	std::cout << "Echec Audsley : " << audsleyFail << std::endl;
	std::cout << "Echec Simulation : "<< simFail << std::endl;
	int totSucceed = REPEAT - audsleyFail - simFail;
	std::cout << "Simulation réussie: "<< totSucceed << std::endl;
	if (totSucceed>0) {
		std::cout << "Preemption moyen : " << float(preemption)/totSucceed << std::endl;
		std::cout << "Repos CPU moyen : " << float(idleTime)/totSucceed << std::endl;
		std::cout << "Temps swap moyen : " << float(swapTime)/totSucceed << std::endl;
		std::cout << "Nb spap moyen : " << float(swapCpt)/totSucceed << std::endl;
		std::cout << "Utilisation moyenne : " << float(ut)*100/totSucceed << "%" << std::endl;
		std::cout << "Charge système moyenne : " << float(sysLoad)*100/totSucceed << "%" << std::endl;
		std::cout << "Longueur simulation moyenne : " << float(simLength)/totSucceed << std::endl;
	}
	std::cout << std::endl;
}

void Study::run(){
	run(H_UTILIZATION,H_MEMORY,H_NBTASKS,"test/1-HHH.tsk","(H,H,H)");
	run(H_UTILIZATION,H_MEMORY,L_NBTASKS,"test/2-HHL.tsk","(H,H,L)");
	run(H_UTILIZATION,L_MEMORY,H_NBTASKS,"test/3-HLH.tsk","(H,L,H)");
	run(H_UTILIZATION,L_MEMORY,L_NBTASKS,"test/4-HLL.tsk","(H,L,L)");
	run(L_UTILIZATION,H_MEMORY,H_NBTASKS,"test/5-LHH.tsk","(L,H,H)");
	run(L_UTILIZATION,H_MEMORY,L_NBTASKS,"test/6-LHL.tsk","(L,H,L)");
	run(L_UTILIZATION,L_MEMORY,H_NBTASKS,"test/7-LLH.tsk","(L,L,H)");
	run(L_UTILIZATION,L_MEMORY,L_NBTASKS,"test/8-LLL.tsk","(L,L,L)");
}


Study::~Study() {
	// TODO Auto-generated destructor stub
}

