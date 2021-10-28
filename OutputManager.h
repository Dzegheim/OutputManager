#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

/**
 * @author [Dzegheim](https://github.com/Dzegheim)
 * @copyright [cc0-1.0](https://creativecommons.org/publicdomain/zero/1.0/deed.en)
 * @date 16-02-2021
 * @version 0.8
 */

#include <iostream>
#include <iomanip>

/**
 * @brief This class is used to easily format output.
 * 
 * @details OutputManager is a class used to simply manage output with various pre-built functions to format many types of printable data.
 * @details The main inspiration is the `print()` function from the python programming language, after which I developed some form of Stockholm syndrome.
 * @tparam OutType The type of the output stream.
 * @tparam StringType The type of the separator and and of line strings.
 * @warning `StringType` must be compatible with `OutType`.
 */
template<typename OutType = std::wostream, typename StringType = std::wstring> class OutputManager {
	protected:
		/**
		 * @brief A reference to any output stream, that will be used to write to. Default is `std::wcout`.
		 */
		OutType& OutStream__;
		/**
		 * @brief The separator character between various outputs on the same line. Default is `L" "`.
		 *
		 * @details This string is automatically inserted between each printed element on the same line.
		 * @see SetSeparator(StringType&&)
		 */
		StringType Separator__;
		/**
		 * @brief The character at the end of a line. Default is `L"\n"`.
		 *
		 * @details This string is automatically inserted between each printed line.
		 * @see SetEndOfLine(StringType&&)
		 */
		StringType EndOfLine__;
		/**
		 * @brief The minimum width of the output, used to format columns if needed. Default is `0`.
		 * @see SetWidth(size_t)
		 */
		size_t Width__ = 0;
		
	public:
		OutputManager(OutputManager const&) = delete;
    	OutputManager& operator=(OutputManager const &) = delete;

		/**
		 * @brief The default constructor sets all variables to their default value.
		 * 
		 * @note Alignment of text is defaulted to left. To change it use SetAlignment(int).
		 */
		OutputManager();
		/**
		 * @brief Only the `OutStream__` attribute is initialised.
		 * 
		 * @note Alignment of text is defaulted to left. To change it use SetAlignment(int).
		 */
		OutputManager(OutType& OutStream);
		/**
		 * @brief Only the `Separator__` and EndOfLine__ attributes are initialised.
		 * 
		 * @note Alignment of text is defaulted to left. To change it use SetAlignment(int).
		 */
		OutputManager(StringType&& Separator, StringType&& EndOfLine);
		/**
		 * @brief All parameters are initialised.
		 * 
		 * @note Alignment of text is defaulted to left. To change it use SetAlignment(int).
		 */
		OutputManager(OutType& OutStream, StringType&& Separator, StringType&& EndOfLine);



		/**
		 * @brief Prints the `EndOfLine__` attribute.
		 */
	    void operator()();
		/** 
		 * @brief Prints a single parameter of any type.
		 *
		 * @details Prints the `ToPrint` parameter, then `EndOfLine__`.
		 * @warning The type `T` must be printable with `operator<<`.
		 * @tparam T A printable type.
		 * @see operator()(T&& ToPrint, P&&... ToPass)
		 */
	    template<typename T> void operator()(T&& ToPrint);
		/** 
		 * @brief Prints many parameters on a single line.
		 * 
		 * @details Prints the `ToPrint` parameter, then the `Separator__`. Recursively calls itself with the `ToPass` parameter as argument until there is only one argument left, then it calls operator()(T&&) to conclude.
		 * @warning The type `T` must be printable with `operator<<`.
		 * @tparam T A printable type.
		 * @tparam P A pack of printable types.
		 * @see operator()(T&& ToPrint)
		 */
		template<typename T, typename... P> void operator()(T&& ToPrint, P&&... ToPass);

		/**
		 * @brief Prints all elements in range.
		 * 
		 * @details Prints all elements in the range separated by the `Separator__` attribute, then prints `EndOfLine__`.
		 * @warning No control is performed on the passed range.
		 * @tparam It A  Forward interator.
		 * @param Begin Begin of range to print.
		 * @param End End of range to print.
		 */
		template<typename It> void PrintRange(It Begin, It End);
		/**
		 * @brief Prints in columns.
		 *
		 * @details Iterates over all given arguments and prints the data in columns, row by row.
		 * 
		 * **Example:**
		 * ```.cpp
		 * #include <vector>
		 * #include <string>
		 * #include "OutputManager.h"
		 * 
		 * int main () {
		 *     std::vector<int> Numbers {1, 2, 3, 4, 5};	
		 *     std::vector<double> Floats {1.1, 2.1, 3.1, 4.1, 5.1};	
		 *     std::vector<std::wstring> Words {L"Cat", L"Dog", L"Mouse", L"Cow", L"Salmon"};
		 *     OutputManager O;
		 *     O.FormatToColumns(Numbers.begin(), Numbers.end(), Floats.begin(), Words.begin());
		 * }
		 * ```
		 * **Output:**
		 * ```
		 * 1 1.1 Cat
		 * 2 2.1 Dog
		 * 3 3.1 Mouse
		 * 4 4.1 Cow
		 * 5 5.1 Salmon
		 * ```
		 * @tparam It A forward iterator.
		 * @tparam Its A pack of forward iterators.
		 * @param Begin Begin of the range to be printed in the first column.
		 * @param End End of the range to be printed in the first column.
		 * @param Others Begin of the other ranges, printed in order. The number of elements printed is the distance between `Begin` and `End`.
		 * @warning No control is performed on the passed ranges, every iterator passed in `Others` must cover a range at least as long as the distance between `Begin` and `End`.
		 */
		template<typename It, typename... Its> void FormatToColumns(It Begin, It End, Its... Others);
		/**
		 * @brief Prints in rows.
		 * 
		 * @details Iterates over all given elements and prints the data in rows, range by range.
		 * 
		 * **Example:**
		 * ```.cpp
		 * #include <vector>
		 * #include <string>
		 * #include "OutputManager.h"
		 * 
		 * int main () {
		 *     std::vector<int> Numbers {1, 2, 3, 4, 5};	
		 *     std::vector<double> Floats {1.1, 2.1, 3.1, 4.1, 5.1};	
		 *     std::vector<std::wstring> Words {L"Cat", L"Dog", L"Mouse", L"Cow", L"Salmon"};
		 *     OutputManager O;
		 *     O.FormatToRows(Numbers.begin(), Numbers.end(), Floats.begin(), Words.begin());
		 * }
		 * ```
		 * **Output:**
		 * ```
		 * 1 2 3 4 5	
		 * 1.1 2.1 3.1 4.1 5.1
		 * Cat Dog Mouse Cow Salmon
		 * ```
		 * @tparam It A forward iterator.
		 * @tparam Its A pack of forward iterators.
		 * @param Begin Begin of the range to be printed in the first line.
		 * @param End End of the range to be printed in the first line.
		 * @param Others Begin of the other ranges, printed in order. The number of elements printed is the distance between `Begin` and `End`.
		 * @warning No control is performed on the passed ranges, every iterator passed in `Others` must cover a range at least as long as the distance between `Begin` and `End`.
		 */
		template<typename It, typename... Its> void FormatToRows(It Begin, It End, Its... Others);
		/**
		 * @brief Prints only the first `N` elements of the given ranges in rows.
		 * 
		 * @details Iterates over all given elements and prints the first `N` elements of each range in rows, range by range.
		 * 
		 * **Example:**
		 * ```.cpp
		 * #include <vector>
		 * #include <string>
		 * #include "OutputManager.h"
		 * 
		 * int main () {
		 *     std::vector<int> Numbers {1, 2, 3, 4, 5};	
		 *     std::vector<double> Floats {1.1, 2.1, 3.1, 4.1, 5.1};	
		 *     std::vector<std::wstring> Words {L"Cat", L"Dog", L"Mouse", L"Cow", L"Salmon"};
		 *     OutputManager O;
		 *     O.FirstNElementsRows(3, Numbers.begin(), Floats.begin(), Words.begin());
		 * }
		 * ```
		 * **Output:**
		 * ```
		 * 1 2 3
		 * 1.1 2.1 3.1	
		 * Cat Dog Mouse
		 * ```
		 * @tparam It A forward iterator.
		 * @tparam Its A pack of forward iterators.
		 * @param Begin Begin of the range to be printed in the first line.
		 * @param Others Begin of the other ranges, printed in order.
		 * @warning No control is performed on the passed ranges, every iterator passed must cover a range long at least N.
		 */
		template<typename It, typename... Its> void FirstNElementsRows(size_t N, It Begin, Its... Others);

		/**
		 * @brief Set the Width object
		 * 
		 * @details **Example:**
		 * ```.cpp
		 * #include <vector>
		 * #include <string>
		 * #include "OutputManager.h"
		 * 
		 * int main () {
		 *     std::vector<int> Numbers {1, 2, 3, 4, 5};	
		 *     std::vector<double> Floats {1.1, 2.1, 3.1, 4.1, 5.1};	
		 *     std::vector<std::wstring> Words {L"Cat", L"Dog", L"Mouse", L"Cow", L"Salmon"};
		 *     OutputManager O;
		 *     O.SetWidth(5);
		 *     O.FormatToColumns(Numbers.begin(), Numbers.end(), Floats.begin(), Words.begin());
		 * }
		 * ```
		 * **Output:**
		 * ```
		 * 1     1.1     Cat  
		 * 2     2.1     Dog  
		 * 3     3.1     Mouse
		 * 4     4.1     Cow  
		 * 5     5.1     Salmon
		 * ```
		 * @param Width The minimum width (in characters) of each column of the output.
		 */
		void SetWidth(size_t Width);
		/**
		 * @brief Sets the `Separator__` attribute.
		 * @param Separator The new separator string.
		 */
		void SetSeparator(StringType&& Separator);
		/**
		 * @brief Sets the `EndOfLine__` attribute.
		 * @param EndOfLine The new end of line string.
		 */
		void SetEndOfLine(StringType&& EndOfLine);
		/**
		 * @brief Sets the alignment of text.
		 * @param Alignment If the parameter is `0` the text is set to `std::internal`, if it's positive the text is set to `std::left`, if it's negative the text is set to `std::right`.
		 */
		void SetAlignment(int Alignment);
		/**
		 * @brief Sets the output precision.
		 * @param Precision The number of decimal places.
		 */
		void SetPrecision(size_t Precision);
		/**
		 * @brief Sets the float formatting flags.
		 * 
		 * @details Switches between `std::fixed`, `std::scientific` and default for the output mode of floating point decimals.
		 * @param Mode If the parameter is `0` the floating point formatting is set to default, if it's positive the formatting is set to `std::fixed`, if it's negative it is set to `std::scientific`.
		 */
		void SetFloatMode (int Mode);
};

//
//CONSTRUCTORS
//
template<typename OutType, typename StringType>
OutputManager<OutType, StringType> ::OutputManager() : OutStream__{std::wcout}, Separator__{L" "}, EndOfLine__{L"\n"} {
	SetAlignment(1);
}

template<typename OutType, typename StringType>
OutputManager<OutType, StringType> ::OutputManager(OutType& OutStream) : OutStream__{OutStream}, Separator__{L" "}, EndOfLine__{L"\n"} {
	SetAlignment(1);
}

template<typename OutType, typename StringType>
OutputManager<OutType, StringType> ::OutputManager(StringType&& Separator, StringType&& EndOfLine) : OutStream__{std::wcout}, Separator__{Separator}, EndOfLine__{EndOfLine} {
	SetAlignment(1);
}

template<typename OutType, typename StringType>
OutputManager<OutType, StringType> ::OutputManager(OutType& OutStream, StringType&& Separator, StringType&& EndOfLine) : OutStream__{OutStream}, Separator__{Separator}, EndOfLine__{EndOfLine} {
	SetAlignment(1);
}

//
//OPERATORS
//
template<typename OutType, typename StringType>
void OutputManager<OutType, StringType> ::operator()() {
	OutStream__ << EndOfLine__;
}

template<typename OutType, typename StringType>
template<typename T>
void OutputManager<OutType, StringType> ::operator()(T&& ToPrint) {
	OutStream__ << std::setw(Width__) << ToPrint << EndOfLine__;
}

template<typename OutType, typename StringType>
template<typename T, typename...P>
void OutputManager<OutType, StringType> ::operator()(T&& ToPrint, P&&... ToPass) {
	OutStream__ << std::setw(Width__) << ToPrint << Separator__;
	operator()(ToPass...);
}

//
//FORMATTERS
//
template<typename OutType, typename StringType>
template<typename It>
void OutputManager<OutType, StringType> ::PrintRange(It Begin, It End) {
	for (;Begin != End; ++Begin) {
		OutStream__ << std::setw(Width__) << *Begin << Separator__;
	}
	OutStream__ << EndOfLine__;
}

template<typename OutType, typename StringType>
template<typename It, typename... Its>
void OutputManager<OutType, StringType> ::FormatToColumns(It Begin, It End, Its... Others) {
	for (;Begin != End; ++Begin) {
		operator()(*Begin, *std::forward<Its>(Others)...);
		//https://www.fluentcpp.com/2019/03/05/for_each_arg-applying-a-function-to-each-argument-of-a-function-in-cpp/
		([](auto&& Iterator){
			std::advance(Iterator, 1);
		}(std::forward<Its>(Others)),...);
	}
	return;
}

template<typename OutType, typename StringType>
template<typename It, typename... Its>
void OutputManager<OutType, StringType> ::FormatToRows(It Begin, It End, Its... Others) {
	PrintRange(Begin, End);
	([&](auto&& NewBegin){
		auto NewEnd = NewBegin;
		std::advance(NewEnd, std::distance(Begin, End));
		PrintRange(NewBegin, NewEnd);
	}(std::forward<Its>(Others)),...);
	return;
}

template<typename OutType, typename StringType>
template<typename It, typename... Its>
void OutputManager<OutType, StringType> ::FirstNElementsRows(size_t N, It Begin, Its... Others) {
	auto End = Begin;
	std::advance (End, N);
	FormatToRows(Begin, End, Others...);
	return;
}

//
//SETTERS
//
template<typename OutType, typename StringType>
void OutputManager<OutType, StringType> ::SetWidth(size_t Width) {
	Width__ = Width;
}

template<typename OutType, typename StringType>
void OutputManager<OutType, StringType> ::SetSeparator(StringType&& Separator) {
	Separator__ = Separator;
}

template<typename OutType, typename StringType>
void OutputManager<OutType, StringType> ::SetEndOfLine(StringType&& EndOfLine) {
	EndOfLine__ = EndOfLine;
}

template<typename OutType, typename StringType>
void OutputManager<OutType, StringType> ::SetAlignment(int Alignment) {
	if (Alignment)
		if (Alignment > 0) {
			 OutStream__ << std::left;
		}
		else {
			OutStream__ << std::right;
		}
	else {
		OutStream__ << std::internal;
	}
}

template<typename OutType, typename StringType>
void OutputManager<OutType, StringType> ::SetPrecision(size_t Precision) {
	OutStream__ << std::setprecision(Precision);
}


template<typename OutType, typename StringType>
void OutputManager<OutType, StringType> ::SetFloatMode(int Mode) {
	if (Mode)
		if (Mode > 0) {
			 OutStream__ << std::fixed;
		}
		else {
			OutStream__ << std::scientific;
		}
	else {
		OutStream__.unsetf(std::ios_base::fixed);
		OutStream__.unsetf(std::ios_base::scientific);
	}
}

#endif