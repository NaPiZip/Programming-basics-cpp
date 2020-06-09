// Copyright 2019, Nawin

#include "Workspace.h"

void TextProcessor::append_list(const std::vector<std::string>& items) {
  list_strategy_->start(oss_);
  for (auto& item : items)
    list_strategy_->add_list_item(oss_, item);
  list_strategy_->end(oss_);
}

void TextProcessor::clear() {
  oss_.str("");
  oss_.clear();
}

void TextProcessor::set_output_format(const OutputFormat format) {
  switch (format) {
  case OutputFormat::markdown:
    list_strategy_ = std::make_unique<MarkdownListStrategy>();
    break;
  case OutputFormat::html:
    list_strategy_ = std::make_unique<HtmlListStrategy>();
    break;
  default:
    break;
  }
}

std::string TextProcessor::str() const{
  return oss_.str();
}

void HtmlListStrategy::start(std::ostringstream& oss) {
  oss << "<ul>\n";
}
void HtmlListStrategy::end(std::ostringstream& oss) {
  oss << "</ul>\n";
}

void HtmlListStrategy::add_list_item(std::ostringstream& oss, const std::string& item) {
  oss << "\t<li>" << item << "</li>\n";
}

void MarkdownListStrategy::add_list_item(std::ostringstream& oss, const std::string& item) {
  oss << " * " << item << std::endl;
}