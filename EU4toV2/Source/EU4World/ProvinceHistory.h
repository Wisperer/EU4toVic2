/*Copyright(c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */



#ifndef PROVINCE_HISTORY_H_
#define PROVINCE_HISTORY_H_



#include "Date.h"
#include "PopRatio.h"
#include "newParser.h"
#include <map>
#include <optional>
#include <vector>
#include <string>



namespace EU4
{

class ProvinceHistory: commonItems::parser
{
	public:
		ProvinceHistory(std::istream& theStream);

		std::optional<date> getFirstOwnedDate() const;
		bool ownedByOriginalOwner() const;
		bool wasInfidelConquest(const std::string& ownerReligionString, bool wasColonized, int num) const;
		date getLastPossessedDate(const std::string& tag) const;

		std::vector<PopRatio> getPopRatios() const { return popRatios; }

	private:
		void buildPopRatios();
		void decayPopRatios(const date& oldDate, const date& newDate, EU4::PopRatio& currentPop);

		std::vector<std::pair<date, std::string>> ownershipHistory;
		std::map<std::string, date> lastPossessedDate;
		std::vector<std::pair<date, std::string>> religionHistory;
		std::vector<std::pair<date, std::string>> cultureHistory;

		std::vector<PopRatio> popRatios;
};

}



#endif // PROVICNE_HISTORY_H_