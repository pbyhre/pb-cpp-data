#include <string>
#include <algorithm>
#include <regex>

namespace pb {

inline std::string ltrim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) {
        return ""; // String is all whitespace
    }
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

inline std::string rtrim(const std::string& str) {
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (end == std::string::npos) {
        return ""; // String is all whitespace
    }
    return str.substr(0, end + 1);
}

inline std::string trim(const std::string& str) {
    return rtrim(ltrim(str));
}

inline std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

/**
 * This function checks for optional whitespace, an optional sign, digits with optional decimal, 
 * and optional scientific notation (e.g., "1.23e-4"). It returns true if the string is numeric, 
 * false otherwise.
 */
inline bool is_numeric(const std::string& str) {
    static const std::regex pattern(R"(^\s*[-+]?\d*\.?\d+(e[-+]?\d+)?\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}

/**
 * This function checks if a string is an integer. It uses a regular expression to match 
 * the following pattern:
 *   - Optional whitespace
 *   - Optional sign (either + or -)
 *   - One or more digits   
 */
inline bool is_integer(const std::string& str) {
    static const std::regex pattern(R"(^\s*[-+]?\d+\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}   

/**
 * This function checks if a string is a valid hexadecimal number. It uses a regular expression to match
 * the following pattern:       
 *   - Optional whitespace
 *   - 0x or 0X prefix
 *   - One or more hexadecimal digits (0-9, a-f, A-F)
 */
inline bool is_hexadecimal(const std::string& str) {
    static const std::regex pattern(R"(^\s*0[xX][0-9a-fA-F]+\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}   

/**
 * This function checks if a string is a valid octal number. It uses a regular expression to match
 * the following pattern:
 *   - Optional whitespace
 *   - 0o or 0O prefix
 *   - One or more octal digits (0-7)
 */
inline bool is_octal(const std::string& str) {
    static const std::regex pattern(R"(^\s*0[oO]?[0-7]+\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}   

/**
 * This function checks if a string is a valid binary number. It uses a regular expression to match
 * the following pattern:
 *   - Optional whitespace
 *   - 0b or 0B prefix
 *   - One or more binary digits (0 or 1)
 */
inline bool is_binary(const std::string& str) {
    static const std::regex pattern(R"(^\s*0[bB][01]+\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}

/**
 * This function checks if a string is a valid double-precision floating-point number. It uses a regular expression to match
 * the following pattern:
 *   - Optional whitespace
 *   - Optional sign (either + or -)
 *   - Zero or more digits before the decimal point
 *   - Optional decimal point followed by zero or more digits
 *   - Optional exponent part (e.g., e-10)
 */

/**
 * This function checks if a string is a valid double-precision floating-point number that requires a decimal point.
 * It uses a regular expression to match the following pattern:
 *   - Optional whitespace
 *   - Optional sign (either + or -)
 *   - One or more digits before the decimal point
 *   - A required decimal point
 *   - One or more digits after the decimal point
 *   - Optional exponent part (e.g., e-10)
 */
inline bool is_double(const std::string& str) {
    static const std::regex pattern(R"(^\s*[-+]?\d+\.\d+(e[-+]?\d+)?\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}

/**
 * This function checks if a string is a valid double-precision floating-point number that may or may not have a decimal point.
 * It uses a regular expression to match the following pattern:
 *   - Optional whitespace
 *   - Optional sign (either + or -)    
 *   - One or more digits before the decimal point
 *   - An optional decimal point
 *   - One or more digits after the decimal point
 *   - Optional exponent part (e.g., e-10)
 */
inline bool is_double_with_optional_decimal(const std::string& str) {
    static const std::regex pattern(R"(^\s*[-+]?\d*\.?\d+(e[-+]?\d+)?\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}

/**
 * This function checks if a string is a valid boolean value. It uses a regular expression to match
 * the following pattern:
 *   - Optional whitespace
 *   - The keywords "true" or "false"
 *   - The integer values 1 or 0
 */
inline bool is_boolean(const std::string& str) {
    static const std::regex pattern(R"(^\s*(true|false|1|0)\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}

/**
 * This function checks if a string is a valid real number. It uses a regular expression to match
 * the following pattern:
 *   - Optional whitespace
 *   - Optional sign (either + or -)
 *   - At least one digit before the decimal point
 *   - Optional decimal point followed by one or more digits
 *   - Optional exponent part (e.g., e-10)
 */
inline bool is_real_number(const std::string& str) {
    static const std::regex pattern(R"(^\s*[-+]?\d+(\.\d+)?([eE][-+]?\d+)?\s*$)", std::regex::icase);
    return std::regex_match(str, pattern);
}

/**
 * The is_date function in this file checks if a given string matches common date formats using 
 * regular expressions. It trims whitespace from the input string and then tests it against several 
 * regex patterns, including:
 *
 * YYYY-MM-DD or YYYY/MM/DD
 * DD-MM-YYYY or DD/MM/YYYY
 * MM-DD-YYYY or MM/DD/YYYY
 * YYYY-MM-DD HH:MM:SS (with optional T, milliseconds, and timezone)
 * ISO 8601 date and datetime formats
 * Month name formats (e.g., "Jan 1, 2020" or "1 Jan 2020")
 * 
 * If the string matches any of these patterns, the function returns true; otherwise, it returns false.
 */
inline bool is_date(const std::string& str) {
    static const std::regex date_patterns[] = {
        // YYYY-MM-DD or YYYY/MM/DD
        std::regex(R"(^\d{4}[-/]\d{2}[-/]\d{2}$)"),
        // DD-MM-YYYY or DD/MM/YYYY
        std::regex(R"(^\d{2}[-/]\d{2}[-/]\d{4}$)"),
        // MM-DD-YYYY or MM/DD/YYYY
        std::regex(R"(^\d{2}[-/]\d{2}[-/]\d{4}$)"),
        // YYYY-MM-DD HH:MM:SS (with optional T and milliseconds)
        std::regex(R"(^\d{4}-\d{2}-\d{2}[ T]\d{2}:\d{2}:\d{2}(\.\d+)?(Z|[+-]\d{2}:\d{2})?$)"),
        // ISO 8601 (date only or datetime)
        std::regex(R"(^\d{4}-\d{2}-\d{2}(T\d{2}:\d{2}:\d{2}(.\d+)?(Z|[+-]\d{2}:\d{2})?)?$)"),
        // Month name formats (e.g., Jan 1, 2020 or 1 Jan 2020)
        std::regex(R"(^([A-Za-z]{3,9})\s+\d{1,2},?\s+\d{4}$)"),
        std::regex(R"(^\d{1,2}\s+([A-Za-z]{3,9})\s+\d{4}$)")
    };

    std::string s = pb::trim(str);
    for (const auto& pat : date_patterns) {
        if (std::regex_match(s, pat)) {
            return true;
        }
    }
    return false;
}
} // namespace pb
