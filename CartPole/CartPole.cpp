// CartPole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Global.h"
#include "Env.h"

bool getAction(const double* weight, Observation observation)
{
	double weightedSum =
		weight[0] * get<0>(observation) +
		weight[1] * get<1>(observation) +
		weight[2] * get<2>(observation) +
		weight[3] * get<3>(observation) +
		weight[4];
	if (weightedSum >= 0) {
		return true;
	}
	else {
		return false;
	}
}
double getSumRewardByWeight(const Env& env, const double* weight)
{
	Observation observation = env.reset();
	double sumReward = 0;
	for (int i = 0; i < 1000; i++) {
		bool action = getAction(weight, observation);
		double reward;
		bool done, info;
		tie(ignore, reward, done, info) = env.step(action);
		sumReward += reward;
		if (done) {
			break;
		}
	}
	return sumReward;
}
void getBestResult(const char* algo = "randomGuess")
{
	Env env;
	double bestReward = 0;
	double bestWeight[5]{};
	for (int i = 0; i < 5; i++) {
		bestWeight[i] = randomDouble();
	}
	int timePercentCounter = 0;
	int total = 10000000;
	for (int iter = 0; iter < total; iter++) {
		double curWeight[5]{};
		bool variation = rand() % 5 == 0 ? false : true;
		if (algo == "hillClimbing" && variation) {
			for (int i = 0; i < 5; i++) {
				curWeight[i] += randomDouble(-0.3, 0.3);
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				curWeight[i] = randomDouble();
			}
		}
		double curSumReward = getSumRewardByWeight(env, curWeight);
		if (curSumReward > bestReward) {
			bestReward = curSumReward;
			for (int i = 0; i < 5; i++) {
				bestWeight[i] = curWeight[i];
			}
		}
		if (bestReward >= 200) {
			break;
		}
		if (iter >= timePercentCounter * total / 100)
		{
			int tens = timePercentCounter / 10;
			int ones = timePercentCounter - tens * 10;
			cout << "\b\b\b" << tens << ones << "%";
			timePercentCounter++;
		}
	}
	cout << "\b\b\b" << "done." << endl;
	cout << bestReward << endl;
	for (int i = 0; i < 5; i++) {
		cout << bestWeight[i] << ' ';
	}
	cout << "\b";
}
int main()
{
	srand((unsigned)time(NULL));
	getBestResult("hillClimbing");
}