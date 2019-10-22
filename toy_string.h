#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>

#include "toy_defs.h"



namespace toy_std {

static uint8_t lower_case_array[255] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63, 64,
	97, 98, 99,
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
	110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122,
	91, 92, 93, 94, 95, 96, 97, 98, 99,
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
	110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
	130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
	140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
	150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
	170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
	180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
	190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
	200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
	210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
	220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
	230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
	240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
	250, 251, 252, 253, 254
};

class toy_string {

public:
	const char *data_;
	size_t size_;

public:
	toy_string():data_(NULL), size_(0) {}
	toy_string(const char *data): data_(data) { size_ = strlen(data); }
	toy_string(const char *data, size_t size): data_(data), size_(size) {}
	toy_string(const std::string& s) { data_=s.data(); size_=s.size(); }

	inline toy_string& operator= (const char* data) { data_ = data; size_ = strlen(data); return *this; }
	inline long operator- (const toy_string& rhs) { return this->data_-rhs.data(); }
	inline bool operator==(const toy_string& rhs) const {
		if (size_!=rhs.size())
			return false;
		return (0==memcmp(data_, rhs.data(), size_));
	}
	inline bool operator==(const std::string& rhs) const {
		if (size_!=rhs.size())
			return false;
		return (0==memcmp(data_, rhs.data(), size_));
	}
	inline bool operator==(const char* rhs) const {
		if (size_!=strlen(rhs))
			return false;
		return (0==memcmp(data_, rhs, size_));
	}
	inline bool operator!=(const toy_string& rhs) const {
		if (size_!=rhs.size())
			return true;
		return (0!=memcmp(data_, rhs.data(), size_));
	}
	inline bool operator!=(const std::string& rhs) const {
		if (size_!=rhs.size())
			return true;
		return (0!=memcmp(data_, rhs.data(), size_));
	}
	inline bool operator!=(const char* rhs) const {
		if (size_!=strlen(rhs))
			return true;
		return (0!=memcmp(data_, rhs, size_));
	}
	inline char& operator[](size_t pos) { return ((char*)this->data_)[pos]; }
	inline const char& operator[](size_t pos) const { return this->data_[pos]; }

	inline std::string string() const { return std::string(this->data_, this->size_); }

	inline void set(const char *data, size_t size) { this->data_ = data; this->size_ = size; }
	inline void set(const char *data) { this->data_ = data; this->size_ = strlen(data); }
	inline void set(size_t size) { this->data_ = new char[size]; if (this->data_!=NULL) this->size_ = size; }

	inline void set_data(const char *data) { this->data_ = data; }
	inline void set_size(size_t size) { this->size_ = size; }

	inline char *data() { return (char *)this->data_; }
	inline const char *data() const { return (char *)this->data_; }
	inline size_t size() const { return this->size_; }
	inline bool empty() const { return size_==0; }
	inline bool null() const {return data_==NULL; }
	inline void clear(bool bDelete=false) {
		if (bDelete) 
			delete[] data_;
		data_ = NULL;
		size_ = 0;
	}

	inline void debug_print(FILE* fp = stderr) {
		if (this->null()) fprintf(fp, "toy_string: null");
		else if (this->empty()) fprintf(fp, "toy_string: empty");
		else fwrite(this->data_, this->size_, 1, fp);
	}

	inline void write_to(FILE* fp = stdout, bool quote = false) {
		if (quote)
			fputc('"', fp);

		if (unlikely(this->size_==0))
			fwrite("null", 4, 1, fp);
		else
			fwrite(this->data_, this->size_, 1, fp);

		if (quote)
			fputc('"', fp);
	}

	inline toy_string& to_lower_case() {
		char *d = (char *)this->data_;
		for (size_t i=0; i<this->size_; i++)
			d[i] = (char)lower_case_array[(uint8_t)d[i]];

		return *this;
	}

	// lower_case_str must be lower case, otherwise comparasion is not valid
	inline int lower_case_compare(const std::string& lower_case_str) {
		if (likely(this->size_!=lower_case_str.size()))
			return 0;

		int res = 1;
		for (size_t i=0; i<this->size_; i++)
			res &= (lower_case_str[i]==(char)lower_case_array[(uint8_t)this->data_[i]]);

		return res;
	}

	inline toy_string &trim() {
		if (this->empty())
			return *this;

		while ( IsBlank(data_) && size_>0)
			data_++, size_--;

		const char* p = data_+size_-1;
		while ( IsBlank(p) && size_>0)
			p--, size_--;

		return *this;
	}

	inline toy_string &ltrim() {
		if (this->empty())
			return *this;

		while ( IsBlank(data_) && size_>0)
			data_++, size_--;
		return *this;
	}

	inline toy_string &rtrim() {
		if (this->empty())
			return *this;

		const char* p = data_+size_-1;
		while ( IsBlank(p) && size_>0)
			p--, size_--;
		return *this;
	}
	
	inline toy_string &trim(char t) {
		if (this->empty())
			return *this;

		while ( *data_==t && size_>0)
			data_++, size_--;

		const char* p = data_+size_-1;
		while ( *p==t && size_>0)
			p--, size_--;

		return *this;
	}

	inline toy_string &ltrim(char t) {
		if (this->empty())
			return *this;

		while ( *data_==t && size_>0)
			data_++, size_--;
		return *this;
	}

	inline toy_string &rtrim(char t) {
		if (this->empty())
			return *this;

		const char* p = data_+size_-1;
		while ( *p==t && size_>0)
			p--, size_--;
		return *this;
	}

	// return null toy_string when no new lines
	inline toy_string next_line() {
		toy_string ms;
		const char *p = data_;
		const char *data_end = data_ + size_;

		if (unlikely(this->empty()))
			return ms;

		while (*p!='\n' && p<data_end)
			p++;

		if (p==data_) {
			ms.set(data_, 0);
			data_++;
			size_--;
		}
		else if (p<data_end) {
			if (*(p-1)=='\r')
				ms.set(data_, p - data_ - 1);
			else
				ms.set(data_, p-data_);
			p++;
			this->set(p, size_- (p-data_));
		}
		else {
			ms = *this;
			this->data_ = data_end;
			this->size_ = 0;
		}

		return ms;
	}

	inline long advance(size_t n = 0, bool newline = false) { // advance to next n bytes (and advance to next line or end of data if newline is true)
		long ret =0;
		if (n==0)
			return ret;

		const char *p = data_;
		const char *data_end = data_ + size_;

		if (n<=size_) {
			p += n;

			if (newline) {
				while (*p!='\n' && p<data_end)
					p++;
				if (p<data_end)
					p++;
			}
		}
		else {
			p = data_end;
		}

		ret = p-data_;
		data_ = p;
		size_ -= ret;

		return ret;
	}

	bool start_with(const toy_string& s) {
		if (s.size()>size_)
			return false;
		return (0==memcmp(data_, s.data(), s.size()));
	}

	bool start_with(const std::string& s) {
		if (s.size()>size_)
			return false;
		return (0==memcmp(data_, s.data(), s.size()));
	}

	bool start_with(const char* s, size_t n) {
		if (n>size_)
			return false;
		return (0==memcmp(data_, s, n));
	}

	bool start_with(const char* s) {
		size_t n = strlen(s);

		if (n>size_)
			return false;
		return (0==memcmp(data_, s, n));
	}

	bool start_with(const char c) {
		if (size_)
			return (c==data_[0]);
		return false;
	}

	size_t find_last_pos(char c) {
		size_t pos = size_;
		for (size_t i=0; i<size_; i++) {
			if (data_[i]==c)
				pos = i;
		}

		return pos;
	}

	inline int strtok(toy_string* token_array, int array_size, const toy_string& delim, bool left_reserved = true) {
		if (this->empty() || array_size==0)
			return 0;

		const char *data_end = data_ + size_;
		const char *token_start = data_;
		const char *token_end;
		toy_string &token_tail = token_array[array_size-1];

		int count = 0;

		while (token_start<data_end) {
			while ( token_start<data_end && char_in_chars(*token_start, delim.data(), delim.size()))
				token_start++;
			token_end = token_start;
			while ( token_end<data_end && !char_in_chars(*token_end, delim.data(), delim.size()))
				token_end++;
			if (token_end>token_start) {
				if (count<array_size)
					token_array[count].set(token_start, token_end-token_start);
				else if (left_reserved)
					token_tail.set_size(token_end-token_tail.data());

				count++;
			}
			token_start = token_end+1;
		}

		return count;
	}

	inline int strtok(toy_string* token_array, int array_size, const char *delim, bool left_reserved = true) {
		if (this->empty() || array_size==0)
			return 0;

		const char *data_end = data_ + size_;
		const char *token_start = data_;
		const char *token_end;
		toy_string &token_tail = token_array[array_size-1];

		size_t delim_len = strlen(delim);
		int count = 0;

		while (token_start<data_end) {
			while ( token_start<data_end && char_in_chars(*token_start, delim, delim_len))
				token_start++;
			token_end = token_start;
			while ( token_end<data_end && !char_in_chars(*token_end, delim, delim_len))
				token_end++;
			if (token_end>token_start) {
				if (count<array_size)
					token_array[count].set(token_start, token_end-token_start);
				else if (left_reserved)
					token_tail.set_size(token_end-token_tail.data());

				count++;
			}
			token_start = token_end+1;
		}

		return count;
	}

	inline int strtok(toy_string* token_array, int array_size, const char delim, bool left_reserved = true) {
		if (this->empty() || array_size==0)
			return 0;

		const char *data_end = data_ + size_;
		const char *token_start = data_;
		const char *token_end;
		toy_string &token_tail = token_array[array_size-1];

		int count = 0;

		while (token_start<data_end) {
			while ( token_start<data_end && *token_start==delim)
				token_start++;
			token_end = token_start;
			while ( token_end<data_end && *token_end!=delim)
				token_end++;
			if (token_end>token_start) {
				if (count<array_size)
					token_array[count].set(token_start, token_end-token_start);
				else if (left_reserved)
					token_tail.set_size(token_end-token_tail.data());

				count++;
			}
			token_start = token_end+1;
		}

		return count;
	}

public:
	static inline bool char_in_chars(const char character, const char *chars, const size_t chars_len) {
		bool ret = false;

		for (size_t i=0; i<chars_len; i++) {
			if (character==chars[i])
				ret = true;
		}

		return ret;
	}

	static void write_to(const std::string& str, FILE* fp = stdout, bool quote = false) {
		if (quote)
			fputc('"', fp);

		if (unlikely(str.size()==0))
			fwrite("null", 4, 1, fp);
		else
			fwrite(str.data(), str.size(), 1, fp);

		if (quote)
			fputc('"', fp);
	}

	// inline size_t hash() {
	// 	size_t result = 0;
	// 	const char *data_end = data_ + size_;

	// 	for (const char* p=data_; p<data_end; p++)
	// 		result = result*131 + *p;

	// 	return result;
	// }

};

} // namespace my_std

namespace std {
	template <>
	struct hash<toy_std::toy_string> {
		std::size_t operator()(const toy_std::toy_string &key) const {
			size_t seed = 131; // 31 131 1313 13131 131313 etc..
			size_t hash = 0;

			for (size_t i=0; i<key.size(); i++)
				hash = hash * seed + key.data()[i];

			return hash;
		}
	};
}

