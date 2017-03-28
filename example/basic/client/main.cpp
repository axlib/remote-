#include <fst/print.h>
#include <iterator>
#include <fstream>
#include "server_interface.hpp"
#include "rmte/remote_client.hpp"

class Client : public ServerInterface, public rmte::remote_client {
public:
	virtual void CreateFolder(std::string s0)
	{
		return Call(RMTE_FUNC_INFO(ServerInterface::CreateFolder), s0);
	}

	virtual std::string GetId()
	{
		return Call(RMTE_FUNC_INFO(ServerInterface::GetId));
	}

	virtual int MyFunction2(int a, int b, int c)
	{
		return Call(RMTE_FUNC_INFO(ServerInterface::MyFunction2), a, b, c);
	}

	virtual std::vector<std::string> GetNames(std::string client_id)
	{
		return Call(RMTE_FUNC_INFO(ServerInterface::GetNames), client_id);
	}

	virtual void AddName(std::string client_id, std::string name)
	{
		return Call(RMTE_FUNC_INFO(ServerInterface::AddName), client_id, name);
	}

	virtual void SendFile(std::string file_name, std::vector<char> data)
	{
		return Call(RMTE_FUNC_INFO(ServerInterface::SendFile), file_name, data);
	}
};

int main()
{
	Client client;
	client.Connect("localhost", "5000");

	client.CreateFolder("my_files");
	//    client.AddName(client_id, "John");

	std::ifstream testFile("/Users/alexarse/Desktop/pointer.png", std::ios::binary);

	if (testFile.is_open()) {
		std::vector<char> fileContents;
		//    fileContents.reserve(fileSize);
		fileContents.assign(std::istreambuf_iterator<char>(testFile), std::istreambuf_iterator<char>());
		client.SendFile("my_files/pointer.png", fileContents);
	}

	//-----------
	const std::string client_id = client.GetId();
	std::vector<std::string> strs = client.GetNames(client_id);

	for (auto& n : strs) {
		fst::print(n);
	}

	fst::print("Value :", client.MyFunction2(5, 6, 7));

	client.AddName(client_id, "John");

	strs = client.GetNames("abc");

	for (auto& n : strs) {
		fst::print(n);
	}

	client.Close();
	return 0;
}
