// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <string>
#include <sstream>
#include <memory>
#include <vector>

enum class OutputFormat {
  markdown,
  html
};

struct ListStrategy {
  virtual void start(std::ostringstream& oss) {}
  virtual void add_list_item(std::ostringstream& oss, const std::string& item) {}
  virtual void end(std::ostringstream& oss) {}
};

struct TextProcessor {
  void append_list(const std::vector<std::string>& items);
  void clear();
  void set_output_format(const OutputFormat format);

  std::string str() const;

private:
  std::ostringstream oss_;
  std::unique_ptr<ListStrategy> list_strategy_;
};

struct HtmlListStrategy : ListStrategy {
  void start(std::ostringstream&) override;
  void add_list_item(std::ostringstream&, const std::string&) override;
  void end(std::ostringstream&) override;
};

struct MarkdownListStrategy : ListStrategy {
  void add_list_item(std::ostringstream&, const std::string&) override;
};

template <typename LS>
struct StaticTextProcessor {
  void append_list(const std::vector<std::string>& items) {
    list_strategy_.start(oss_);
    for (auto& item : items)
      list_strategy_.add_list_item(oss_, item);
    list_strategy_.end(oss_);
  }
  std::string str() const {
    return oss_.str();
  }

private:
  std::ostringstream oss_;
  LS list_strategy_;
};
  
#endif // _HEADER_WORKSPACE
