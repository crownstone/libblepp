#include <blepp/lescan.h>
//#include <iostream>
#include <fstream>

int main()
{
	//BLEPP::log_level = BLEPP::LogLevels::Info;
	BLEPP::HCIScanner scanner(true, BLEPP::HCIScanner::FilterDuplicates::Off, BLEPP::HCIScanner::ScanType::Passive);

	std::ofstream scan_log;
	scan_log.open ("scan_log.txt");

	while (1) {
		std::vector<BLEPP::AdvertisingResponse> ads = scanner.get_advertisements();

		for(const auto& ad: ads)
		{
			std::cout << "Found device: " << ad.address << " " << std::endl;
			std::cout << "  RSSI = " << std::dec << (int) (ad.rssi) << " dBm" << std::endl;
			std::cout << std::endl;
			for (auto i: ad.raw_packet) {
				for (auto j: i) {
					// A printf("%02x:", j); statement in C++, yeah.
					std::cout << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)(j & 0xFF) << ":";
				}
			}
			std::cout << std::endl;
			scan_log << ad.address << ",";
			scan_log << std::dec << (int)(ad.rssi) << ",";
			for (auto i: ad.raw_packet) {
				for (auto j: i) {
					scan_log << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)(j & 0xFF);
				}
			}
			scan_log << std::endl;
		}
		scan_log << std::flush;
	}
	scan_log.close();
}
