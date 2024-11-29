#ifndef __STAT_H
#define __STAT_H

#include "dash/DashStatistics.h"

class [[deprecated("This class is deprecated. Use dash::StatisticValue instead.")]] Statistic : public dash::StatisticValue<dash::string> {
  private:
    ESPDash* _dashboard;

  public:
    Statistic(ESPDash* dashboard, const char* key, const char* value = "") : dash::StatisticValue<dash::string>(*dashboard, key), _dashboard(dashboard) { set(value); }
    bool set(const char* value) { return dash::StatisticValue<dash::string>::setValue(dash::string(value)); }
    void set(const dash::string& value) { set(value.c_str()); }
    void set(dash::string&& value) { dash::StatisticValue<dash::string>::setValue(std::move(value)); }
    ~Statistic();
};

#endif