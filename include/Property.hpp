#ifndef __Property__hpp__
#define __Property__hpp__

#include "reports.hpp"

struct Property {
    Property() = default;
    ~Property() = default;

    std::string __name_;
    std::string __entrata_name_;
    unsigned    __id_;

    OperationsSummary           __operations_summary_;
    std::vector<BudgetVSActual> __budget_vs_actual_;
    ExecutiveSummaryEntry       __exec_summ_entry_;
};

#endif // __Property__hpp__