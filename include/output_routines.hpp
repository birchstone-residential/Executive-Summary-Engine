#ifndef __output_routines__hpp__
#define __output_routines__hpp__

#include "PropertyList.hpp"
#include "dictionaries.hpp"

// Utility to create output directory
void createOutputDirectory()
{
    std::string path = "data/" + sExportDate + "/bin/";
    std::cout << "~ Creating directory: \t\t (" << path << ")" << std::endl;
    fs::create_directories(path);
}


void writeExecutiveSummary(PropertyList& propList)
{
    static const std::string FILENAME = "data/" + sExportDate + "/bin/Executive Summary.csv";

    std::ofstream outFS(FILENAME, std::ios::out);

    // Write header
    outFS << "Property,"
          << "Date,"
          << "Report Month,"
          << "Metric,"
          << "Value,"
          << "Origin,"
          << "Decoder,"
          << "Section" // add comma if extended

          << std::endl;

    outFS << std::fixed << std::setprecision(2);

    for (auto &prop : propList())
    {
        ///< MARK: Occupancy
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Occupancy," << prop.__operations_summary_.__occupancy_ << "," << "Operations Summary," << "Occupied," << std::endl;
        
        ///< MARK: Revenue
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Revenue - Actual," << prop.__exec_summ_entry_.__revenue_actual_ << "," << "Income Statement," << "1. Revenue," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Revenue - Budget," << prop.__exec_summ_entry_.__revenue_budget_ << "," << "Income Statement," << "1. Revenue," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Revenue - Variance %," << prop.__exec_summ_entry_.__revenue_variance_ << "%," << "Income Statement," << "1. Revenue," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Revenue - Actual - YTD," << prop.__exec_summ_entry_.__revenue_actual_ytd_ << "," << "Income Statement," << "1. Revenue," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Revenue - Budget - YTD," << prop.__exec_summ_entry_.__revenue_budget_ytd_ << "," << "Income Statement," << "1. Revenue," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Revenue - Variance % - YTD," << prop.__exec_summ_entry_.__revenue_variance_ytd_ << "%," << "Income Statement," << "1. Revenue," << std::endl;
        
        ///< MARK: Expenses
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Expense - Actual," << prop.__exec_summ_entry_.__expenses_actual_ << "," << "Calculated," << "2. Expenses," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Expense - Budget," << prop.__exec_summ_entry_.__expenses_budget_ << "," << "Calculated," << "2. Expenses," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Expense - Variance %," << prop.__exec_summ_entry_.__expenses_variance_ << "%," << "Calculated," << "2. Expenses," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Expense - Actual - YTD," << prop.__exec_summ_entry_.__expenses_actual_ytd_ << "," << "Calculated," << "2. Expenses," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Expense - Budget - YTD," << prop.__exec_summ_entry_.__expenses_budget_ytd_ << "," << "Calculated," << "2. Expenses," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Expense - Variance % - YTD," << prop.__exec_summ_entry_.__expenses_variance_ytd_ << "%," << "Calculated," << "2. Expenses," << std::endl;

        ///< MARK: NOI
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "NOI - Actual," << prop.__exec_summ_entry_.__noi_actual_ << "," << "Calculated," << "3. NOI," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "NOI - Budget," << prop.__exec_summ_entry_.__noi_budget_ << "," << "Calculated," << "3. NOI," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "NOI - Variance %," << prop.__exec_summ_entry_.__noi_variance_ << "%," << "Calculated," << "3. NOI," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "NOI - Actual - YTD," << prop.__exec_summ_entry_.__noi_actual_ytd_ << "," << "Calculated," << "3. NOI," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "NOI - Budget - YTD," << prop.__exec_summ_entry_.__noi_budget_ytd_ << "," << "Calculated," << "3. NOI," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "NOI - Variance % - YTD," << prop.__exec_summ_entry_.__noi_variance_ytd_ << "%," << "Calculated," << "3. NOI," << std::endl;
        
        ///< MARK: Capital
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Capital - Actual," << prop.__exec_summ_entry_.__capital_actual_ << "," << "Calculated," << "4. Capital," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Capital - Budget," << prop.__exec_summ_entry_.__capital_budget_ << "," << "Calculated," << "4. Capital," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Capital - Variance %," << prop.__exec_summ_entry_.__capital_variance_ << "%," << "Calculated," << "4. Capital," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Capital - Actual - YTD," << prop.__exec_summ_entry_.__capital_actual_ytd_ << "," << "Calculated," << "4. Capital," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Capital - Budget - YTD," << prop.__exec_summ_entry_.__capital_budget_ytd_ << "," << "Calculated," << "4. Capital," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Capital - Variance % - YTD," << prop.__exec_summ_entry_.__capital_variance_ytd_ << "%," << "Calculated," << "4. Capital," << std::endl;

        ///< MARK: Net Income
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Net Income - Actual," << prop.__exec_summ_entry_.__net_income_actual_ << "," << "Calculated," << "5. Net Income," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Net Income - Budget," << prop.__exec_summ_entry_.__net_income_budget_ << "," << "Calculated," << "5. Net Income," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Net Income - Variance %," << prop.__exec_summ_entry_.__net_income_variance_ << "%," << "Calculated," << "5. Net Income," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Net Income - Actual - YTD," << prop.__exec_summ_entry_.__net_income_actual_ytd_ << "," << "Calculated," << "5. Net Income," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Net Income - Budget - YTD," << prop.__exec_summ_entry_.__net_income_budget_ytd_ << "," << "Calculated," << "5. Net Income," << std::endl;
        outFS << prop.__name_ << "," << reformatDateAs_MMDDYYYY(sExportDate_Forward_Slash_Format) << "," << getReportDateAs_MMYYYY(sExportDate_Forward_Slash_Format) << "," << "Net Income - Variance % - YTD," << prop.__exec_summ_entry_.__net_income_variance_ytd_ << "%," << "Calculated," << "5. Net Income," << std::endl;
    }

    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {   
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

#endif // __output_routines__hpp__
