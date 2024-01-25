#ifndef __ANALYSISHUB_INC__
#define __ANALYSISHUB_INC__

#include "EnterSymbol.h"
namespace air
{
    struct AnalysisHub
    {
        AnalysisHub(Project &project) : project(project)
        {
            init();
            start();
        }

        private:
        std::vector<AstVisRef> passlist;
        Project &project;
        void init();
        void start();
    };
}
#endif // __ANALYSISHUB_INC__