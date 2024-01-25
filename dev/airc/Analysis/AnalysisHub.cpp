#include "AnalysisHub.h"

namespace air
{
    void AnalysisHub::init()
    {
        passlist.emplace_back(std::make_shared<EnterSymbol>(project));
    }

    void AnalysisHub::start()
    {
        for(auto &item:project.filemap){
            auto& unit=item.second;
            for(auto&pass:passlist)
                pass->start(unit);
        }
    }
}