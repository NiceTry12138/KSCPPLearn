#include <iostream>
#include "OCtreeManager.h"
using namespace std;

int main() {

	auto Manager = OCtreeManager(Vector3(), Size(1000.0, 1000.0, 1000.0));
	for (int i = 0; i < 50; i++)
	{
		for (int x = 0; x < 2; ++x)
		{
			for (int y = 0; y < 2; ++y)
			{
				for (int z = 0; z < 2; ++z)
				{
					Vector3 NewNodeCenterPos;
					NewNodeCenterPos.X = 20.0 / 2 * IS_1(x) * i;
					NewNodeCenterPos.Y = 20.0 / 2 * IS_1(y) * i;
					NewNodeCenterPos.Z = 20.0 / 2 * IS_1(z) * i;

					//std::cout << NewNodeCenterPos.to_string() << std::endl;

					std::string Data = std::to_string(i) + "_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
					Manager.AddData(Data, NewNodeCenterPos);
				}
			}
		}
	}
	Manager.PrintAllData();
	return 0;
}