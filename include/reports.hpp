#ifndef __reports__hpp__
#define __reports__hpp__

#include <vector>

struct OperationsSummary
{
    std::string __property_;
    double __occupancy_;
    double __leased_;
};

struct BudgetVSActual
{
    // Property,"Account Name","Jun 2025 - Actual","Jun 2025 - Budget","Jun 2025 - $ Variance","Jun 2025 - % Variance","YTD ( Jan 2025 - Jun 2025 ) - Actual","YTD ( Jan 2025 - Jun 2025 ) - Budget","YTD ( Jan 2025 - Jun 2025 ) - $ Variance","YTD ( Jan 2025 - Jun 2025 ) - % Variance","Annual Budget"
    std::string __property_;
    std::string __account_name_;

    double __prior_month_actual_;
    double __prior_month_budget_;
    double __prior_month_dollar_variance_;
    double __prior_month_percent_variance_;
    double __ytd_actual_;
    double __ytd_budget_;
    double __ytd_dollar_variance_;
    double __ytd_percent_variance_;
    double __annual_budget_;
};

struct ExecutiveSummaryEntry
{
    std::string __property_;

    // revenue
    double __revenue_actual_ = 0.f;
    double __revenue_actual_ytd_ = 0.f;
    double __revenue_budget_ = 0.f;
    double __revenue_budget_ytd_ = 0.f;
    double __revenue_variance_ = 0.f;
    double __revenue_variance_ytd_ = 0.f;
    // expenses
    double __expenses_actual_ = 0.f;
    double __expenses_actual_ytd_ = 0.f;
    double __expenses_budget_ = 0.f;
    double __expenses_budget_ytd_ = 0.f;
    double __expenses_variance_ = 0.f;
    double __expenses_variance_ytd_ = 0.f;
    // noi
    double __noi_actual_ = 0.f;
    double __noi_actual_ytd_ = 0.f;
    double __noi_budget_ = 0.f;
    double __noi_budget_ytd_ = 0.f;
    double __noi_variance_ = 0.f;
    double __noi_variance_ytd_ = 0.f;
    // capital
    double __capital_actual_ = 0.f;
    double __capital_actual_ytd_ = 0.f;
    double __capital_budget_ = 0.f;
    double __capital_budget_ytd_ = 0.f;
    double __capital_variance_ = 0.f;
    double __capital_variance_ytd_ = 0.f;
    // net income
    double __net_income_actual_ = 0.f;
    double __net_income_actual_ytd_ = 0.f;
    double __net_income_budget_ = 0.f;
    double __net_income_budget_ytd_ = 0.f;
    double __net_income_variance_ = 0.f;
    double __net_income_variance_ytd_ = 0.f;

    // all other expenses
    double __other_expenses_actual_ = 0.f;
    double __other_expenses_actual_ytd_ = 0.f;
    double __other_expenses_budget_ = 0.f;
    double __other_expenses_budget_ytd_ = 0.f;
    double __other_expenses_variance_ = 0.f;
    double __other_expenses_variance_ytd_ = 0.f;

    // miscellaneous category
    double __misc_category_actual_ = 0.f;
    double __misc_category_actual_ytd_ = 0.f;
    double __misc_category_budget_ = 0.f;
    double __misc_category_budget_ytd_ = 0.f;
    double __misc_category_variance_ = 0.f;
    double __misc_category_variance_ytd_ = 0.f;
};

#endif // __reports__hpp__