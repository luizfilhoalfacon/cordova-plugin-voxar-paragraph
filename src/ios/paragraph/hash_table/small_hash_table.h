#ifndef __GUARD_SMALL_HASH_TABLE_H__
#define __GUARD_SMALL_HASH_TABLE_H__

#ifdef __USEVOXARPARAGRAPH__
#include "voxarparagraph/hash_table/HashTable.h"
#else
#include "hash_table/HashTable.h"
#endif

class Small_Hash_Table : HashTable {

public:
    typedef std::unordered_map<unsigned int, std::pair<document_id_type, Point2> > map_type;

    typedef map_type::iterator iterator;
    typedef map_type::const_iterator const_iterator;
    typedef map_type::size_type size_type;
	
private:
	iterator begin() { return m_data.begin(); }
	iterator end() { return m_data.end(); }
	iterator find(unsigned int key);


	iterator erase(const_iterator position);
	size_type erase(const unsigned int key);

    
public:
	const_iterator begin() const { return m_data.begin(); }
	const_iterator end() const { return m_data.end(); }
    Small_Hash_Table(unsigned int hash_size, 
        const std::string& page_common_filename = "hash-table-" + std::to_string(timestamp()) + "-page-");
    Small_Hash_Table(unsigned int hash_size, unsigned int n_pages, 
        const std::string& page_common_filename = "hash-table-" + std::to_string(timestamp()) + "-page-");

    // Accessor functions
    unsigned int hash_size() const { return m_hash_size; }
    unsigned int num_pages() const { return m_n_pages; }
    unsigned int page() const { return m_current_page; }
    const std::string& page_filename() const { return m_pages_common_filename; }

    unsigned int page_number(unsigned int key) const;

    void clear() { clear_page(); empty_files(); };


	bool insert(unsigned int key, const std::pair<document_id_type, Point2>& value);

	void get_entries(unsigned int key, std::list<std::pair<document_id_type, Point2> >& dst);

    bool serialize(std::ostream& os);
    bool serialize(const std::string& filename);

    bool deserialize(std::istream& is, bool adjust_pages = true);
    bool deserialize(const std::string& filename, bool adjust_pages = true);

private:
    map_type m_data;
    std::unordered_set<unsigned int> m_forbidden_keys;
    const std::string m_pages_common_filename;
    const unsigned int m_hash_size;
    unsigned int m_n_pages;
    unsigned int m_current_page;
    bool modified;

    static long long timestamp();

    void empty_files();

    bool load_page(unsigned int page);

    void clear_page() { m_data.clear(); m_forbidden_keys.clear(); }

    bool serialize_page(std::ostream& os) const;
    bool serialize_page(const std::string& filename) const;

    bool deserialize_page(std::istream& is, bool should_use_buffer = false, bool should_clear = true);
    bool deserialize_page(const std::string& filename);
};

namespace HashWiki {
	static void getSizes(const Small_Hash_Table &h, SizesType &v) {
		v.clear();
		Small_Hash_Table::const_iterator it = h.begin();
		while (it != h.end()) {
			//if (it->second.size() > 0) {
				v.push_back(std::make_pair((unsigned int)1, (unsigned int)it->first));
			//}
			//break;
			it++;
		}
		std::sort(v.rbegin(), v.rend());
	}
	static void printSizes(SizesType &sizes, const Small_Hash_Table &h) {
		if (HashWikiFile::checkOut()) {
			for (int i = 0; i < sizes.size(); i++) {
				fprintf(HashWikiFile::getOutFile(), "%u;%u\n", sizes[i].second, sizes[i].first);
			}
		}
	}


	static void printStatistics(const Small_Hash_Table &h, std::string fileName = "") {
		if (fileName.size() > 0) {
			HashWikiFile::setFile(fileName);
		}
		if (HashWikiFile::checkOut()) {
			fprintf(HashWikiFile::getOutFile(), "Statistics\n");
			SizesType sizes;
			HashWiki::getSizes(h, sizes);
			HashWiki::printMetrics(sizes);
			HashWiki::printSizes(sizes, h);
		}
	}
};
#endif
