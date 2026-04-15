#ifndef __input_routines__hpp__
#define __input_routines__hpp__

#include "PropertyList.hpp"
#include "helper_functions.hpp"
#include "rapidcsv.h"
#include "dictionaries.hpp"

std::string getHeaderFragment()
{
    std::string formattedDate = reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format);
    std::string priorMonthYear = extractPriorMonthYear(formattedDate);
    return priorMonthYear;
}

std::string getYTDHeaderFragment()
{
    std::string prefix = "YTD ( Jan ";
    std::string headerFragement = getHeaderFragment();
    std::string yearStr = headerFragement.substr(4, 7);
    std::string str = prefix + yearStr + " - " + headerFragement + " )";
    return str;
}

void inputOperationsSummary(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Operations Summary.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of OperationsSummary structs to store the results
    std::vector<OperationsSummary> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        OperationsSummary data;

        data.__property_  = doc.GetCell<std::string>("Property", i);
        data.__occupancy_ = doc.GetCell<double>("Availability - Occupancy", i);
        data.__leased_    = doc.GetCell<double>("Availability - Leased", i);

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__operations_summary_ = item;

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

void inputBudgetVSActual(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Budget vs Actual (Merged).csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Budget VS Actual structs to store the results
    std::vector<BudgetVSActual> vect;

    std::string headerFragment = getHeaderFragment();
    std::string ytdHeaderFragement = getYTDHeaderFragment();
    std::string header = "";

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        BudgetVSActual data;

        data.__property_ = doc.GetCell<std::string>("Property", i);
        data.__account_name_ = doc.GetCell<std::string>("Account Name", i);

        header = headerFragment + " - Actual";
        data.__prior_month_actual_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        ///< DEBUGGING: Input precision
        //if (data.__property_ == "Avery")
        //{
        //    //std::cout << std::fixed << std::setprecision(2) << std::endl;
        //    //std::cout << "as string: " << doc.GetCell<std::string>(header, i) << std::endl;
        //    //std::cout << "parseDouble return: " << parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i)) << std::endl;
        //    //std::cout << "parseDouble return: " << parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i)) << std::endl;
        //    ////std::cout << "direct convert: " << std::stod(doc.GetCell<std::string>(header, i)) << std::endl;
        //    //double val = data.__prior_month_actual_;
        //    //std::cout << "In Input: " << std::fixed << std::setprecision(2) << val << std::endl;
        //}
        

        header = headerFragment + " - Budget";
        data.__prior_month_budget_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        header = headerFragment + " - $ Variance";
        data.__prior_month_dollar_variance_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        header = headerFragment + " - % Variance";
        data.__prior_month_percent_variance_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        header = ytdHeaderFragement + " - Actual";
        data.__ytd_actual_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        header = ytdHeaderFragement + " - Budget";
        data.__ytd_budget_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        header = ytdHeaderFragement + " - $ Variance";
        data.__ytd_dollar_variance_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        header = ytdHeaderFragement + " - % Variance";
        data.__ytd_percent_variance_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>(header, i));

        data.__annual_budget_ = parseDoubleWithCommaAndParentheses(doc.GetCell<std::string>("Annual Budget", i));
        
        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__budget_vs_actual_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

void convertToExecSummEntries(PropertyList& propList) noexcept(false)
{
    for (auto &prop: propList())
    {
        prop.__exec_summ_entry_.__property_ = prop.__name_;
        ExecutiveSummaryEntry& entry = prop.__exec_summ_entry_;

        for (auto &item : prop.__budget_vs_actual_)
        {
            ///< MARK: Revenue
            //////////////////////////////////////////////////////////////////////
            if (item.__account_name_ == "Gross Potential Rent"         ||
                item.__account_name_ == "Rental Revenue Adjustments"   ||
                item.__account_name_ == "Reimbursable/Billback Income" ||
                item.__account_name_ == "Other Income/Losses")
            {
                entry.__revenue_actual_       += item.__prior_month_actual_;
                entry.__revenue_budget_       += item.__prior_month_budget_;
                entry.__revenue_actual_ytd_   += item.__ytd_actual_;
                entry.__revenue_budget_ytd_   += item.__ytd_budget_;
            }
            ///< MARK: Expenses
            //////////////////////////////////////////////////////////////////////
            else if (item.__account_name_ == "Utilities"               ||
                     item.__account_name_ == "Contract Services"       || 
                     item.__account_name_ == "Repairs and Maintenance" || 
                     item.__account_name_ == "Turnover"                || 
                     item.__account_name_ == "Payroll"                 ||
                     item.__account_name_ == "Administrative Expenses" ||
                     item.__account_name_ == "Marketing/L&D"           ||
                     item.__account_name_ == "Taxes and Insurance"     ||
                     item.__account_name_ == "Management Fees")
            {
                entry.__expenses_actual_       += item.__prior_month_actual_;
                entry.__expenses_budget_       += item.__prior_month_budget_;
                entry.__expenses_actual_ytd_   += item.__ytd_actual_;
                entry.__expenses_budget_ytd_   += item.__ytd_budget_;
            }
            ///< MARK: Capital
            //////////////////////////////////////////////////////////////////////
            else if (item.__account_name_.find("CapEx") != SIZE_MAX)
            {
                entry.__capital_actual_       += item.__prior_month_actual_;
                entry.__capital_budget_       += item.__prior_month_budget_;
                entry.__capital_actual_ytd_   += item.__ytd_actual_;
                entry.__capital_budget_ytd_   += item.__ytd_budget_;
            }
            ///< MARK: Other Income
            //////////////////////////////////////////////////////////////////////
            else if (item.__account_name_ == "Other (Income)/Expenses" ||
                     item.__account_name_ == "Depreciation and Amortization" ||
                     item.__account_name_ == "Non-Operating Expenses" ||
                     item.__account_name_ == "Replacements - Turn Cost" ||
                     item.__account_name_ == "Replacements - Exterior" ||
                     item.__account_name_ == "Non-Operating CapEx Reserve" || 
                     item.__account_name_ == "Start Up Costs" ||
                     item.__account_name_ == "Capex - Contra" || 
                     item.__account_name_ == "Capex - Management Fees")
            {

                //if (prop.__name_ == "Avery")
                //{
                //    std::cout << item.__account_name_ << " | " << item.__prior_month_actual_ << std::endl;
                //}

                entry.__other_expenses_actual_       += item.__prior_month_actual_;
                entry.__other_expenses_budget_       += item.__prior_month_budget_;
                entry.__other_expenses_actual_ytd_   += item.__ytd_actual_;
                entry.__other_expenses_budget_ytd_   += item.__ytd_budget_;
            }
            else
            {
                entry.__misc_category_actual_       += item.__prior_month_actual_;
                entry.__misc_category_budget_       += item.__prior_month_budget_;
                entry.__misc_category_actual_ytd_   += item.__ytd_actual_;
                entry.__misc_category_budget_ytd_   += item.__ytd_budget_;
            }
        }

        ///< MARK: Variances
        if (entry.__revenue_budget_ == 0 || entry.__revenue_budget_ == 0)
            entry.__revenue_variance_ = -100.f;
        else
            entry.__revenue_variance_ = ((entry.__revenue_actual_ - entry.__revenue_budget_) / std::abs(entry.__revenue_budget_)) * 100;

        ///////
        if (entry.__revenue_budget_ytd_ == 0 || entry.__revenue_budget_ytd_ == 0)
            entry.__revenue_variance_ytd_ = -100.f;
        else
            entry.__revenue_variance_ytd_ = ((entry.__revenue_actual_ytd_ - entry.__revenue_budget_ytd_) / std::abs(entry.__revenue_budget_ytd_)) * 100;
        
        ///////
        if (entry.__expenses_budget_ == 0 || entry.__expenses_budget_ == 0)
            entry.__expenses_variance_ = -100.f;
        else
            entry.__expenses_variance_ = ((entry.__expenses_actual_ - entry.__expenses_budget_) / std::abs(entry.__expenses_budget_)) * -100;
        
        ///////
        if (entry.__expenses_budget_ytd_ == 0 || entry.__expenses_budget_ytd_ == 0)
            entry.__expenses_variance_ytd_ = -100.f;
        else
            entry.__expenses_variance_ytd_ = ((entry.__expenses_actual_ytd_ - entry.__expenses_budget_ytd_) / std::abs(entry.__expenses_budget_ytd_)) * -100;

        ///////
        if (entry.__capital_budget_ == 0 || entry.__capital_budget_ == 0)
            entry.__capital_variance_ = -100.f;
        else
            entry.__capital_variance_ = ((entry.__capital_actual_ - entry.__capital_budget_) / std::abs(entry.__capital_budget_)) * -100;

        ///////
        if (entry.__capital_budget_ytd_ == 0 || entry.__capital_budget_ytd_ == 0)
            entry.__capital_variance_ytd_ = -100.f;
        else
            entry.__capital_variance_ytd_ = ((entry.__capital_actual_ytd_ - entry.__capital_budget_ytd_) / std::abs(entry.__capital_budget_ytd_)) * -100;

        ///< MARK: NOI
        entry.__noi_actual_       = entry.__revenue_actual_     - entry.__expenses_actual_;
        entry.__noi_budget_       = entry.__revenue_budget_     - entry.__expenses_budget_;
        entry.__noi_variance_     = ((entry.__noi_actual_       - entry.__noi_budget_)     / std::abs(entry.__noi_budget_))     * 100;
        entry.__noi_actual_ytd_   = entry.__revenue_actual_ytd_ - entry.__expenses_actual_ytd_;
        entry.__noi_budget_ytd_   = entry.__revenue_budget_ytd_ - entry.__expenses_budget_ytd_;
        entry.__noi_variance_ytd_ = ((entry.__noi_actual_ytd_   - entry.__noi_budget_ytd_) / std::abs(entry.__noi_budget_ytd_)) * 100;

        ///< MARK: Net Income        
        entry.__net_income_actual_       =   entry.__revenue_actual_        - entry.__capital_actual_         - entry.__other_expenses_actual_       - entry.__expenses_actual_       - entry.__misc_category_actual_;
        entry.__net_income_budget_       =   entry.__revenue_budget_        - entry.__capital_budget_         - entry.__other_expenses_budget_       - entry.__expenses_budget_       - entry.__misc_category_budget_;      
        entry.__net_income_variance_     = ((entry.__net_income_actual_     - entry.__net_income_budget_)     / std::abs(entry.__net_income_budget_))          * 100;
        entry.__net_income_actual_ytd_   =   entry.__revenue_actual_ytd_    - entry.__capital_actual_ytd_     - entry.__other_expenses_actual_ytd_   - entry.__expenses_actual_ytd_   - entry.__misc_category_actual_ytd_;
        entry.__net_income_budget_ytd_   =   entry.__revenue_budget_ytd_    - entry.__capital_budget_ytd_     - entry.__other_expenses_budget_ytd_   - entry.__expenses_budget_ytd_   - entry.__misc_category_budget_ytd_;
        entry.__net_income_variance_ytd_ = ((entry.__net_income_actual_ytd_ - entry.__net_income_budget_ytd_) / std::abs(entry.__net_income_budget_ytd_))      * 100;

        //if (prop.__name_ == "Avery")
        //{
        //    //std::cout << std::fixed << std::setprecision(2);
        //    //std::cout << "For Avery: " << std::endl;
        //    //std::cout << "Net Income Actual:         " << entry.__net_income_actual_ << std::endl;
        //    //std::cout << "Net Income Budget:         " << entry.__net_income_budget_ << std::endl;
        //    //std::cout << "Net Income Variance:       " << entry.__net_income_variance_ << std::endl;
        //    //std::cout << "Net Income Actual YTD:     " << entry.__net_income_actual_ytd_ << std::endl;
        //    //std::cout << "Net Income Budget YTD:     " << entry.__net_income_budget_ytd_ << std::endl;
        //    //std::cout << "Net Income Variance YTD:   " << entry.__net_income_variance_ytd_ << std::endl;
        //
        //    //std::cout << "\t - Revenue Actual:        " << entry.__revenue_actual_ << std::endl;
        //    //std::cout << "\t - Budget Actual:         " << entry.__revenue_budget_ << std::endl;
        //    //std::cout << "\t - Expenses Actual:       " << entry.__expenses_actual_ << std::endl;
        //    //std::cout << "\t - Capital Actual:        " << entry.__capital_actual_ << std::endl;
        //    //std::cout << "\t - Other Expenses Actual: " << entry.__other_expenses_actual_ << std::endl;
        //    //std::cout << "\t - Misc Category:         " << entry.__misc_category_actual_ << std::endl;
        //}
    }
}

#endif // __input_routines__hpp__