#include <string>
#include <vector>
#include <iostream>

namespace pb {

    enum CSVDelimiter {
        UNKNOWN,
        COMMA,
        TAB
    };
    
    enum CSVQuoteStyle {
        NONE,
        DOUBLE,
        SINGLE
    };

    enum CSVDataType {
        STRING,
        INTEGER,
        FLOAT,
        BOOLEAN,
        DATE
    };

    class CSVColumn {
        public:
            CSVColumn(const std::string& name, CSVDataType dataType = STRING)
                : name_(name), dataType_(dataType) {}

            const std::string& get_name() const { return name_; }
            CSVDataType get_data_type() const { return dataType_; }

        private:
            std::string name_;
            CSVDataType dataType_;
    };

    class CSVProperties {
        public:
            CSVProperties() : delimiter_(UNKNOWN) {}

            void add_column(const CSVColumn& column) {
                columns_.push_back(column);
            }

            void set_delimiter(CSVDelimiter delimiter) {
                delimiter_ = delimiter;
            }

            const std::vector<CSVColumn>& getColumns() const {
                return columns_;
            }

            CSVDelimiter get_delimiter() const {
                return delimiter_;
            }

        private:
            std::vector<CSVColumn> columns_;
            CSVDelimiter delimiter_;

    };

    class CSV {
        public:
            // Constructor
            CSV() = default;

            // Method to parse CSV data
            void parse(const std::string& data);

            // Method to get parsed data
            const std::vector<std::vector<std::string>>& getData() const;

        private:
            std::vector<std::vector<std::string>> data_;
    };
    void CSV::parse(const std::string& data) {
        // Implementation of CSV parsing logic
        // This is a placeholder for actual parsing logic
    }   
}