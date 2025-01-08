import React, { useState, useEffect } from 'react';
import { fetchEmployeeData } from '../Services/dataService';
import debounce from 'lodash.debounce';

const SearchBar = ({ onSearch }) => {
  const [searchTerm, setSearchTerm] = useState('');
  const [results, setResults] = useState([]);
  const [data, setData] = useState([]);
  const [showResults, setShowResults] = useState(false);

  useEffect(() => {
    (async () => {
      const employees = await fetchEmployeeData();
      setData(employees);
      setResults(employees);
    })();
  }, []);

  const handleSearch = debounce((term) => {
    if (term) {
      const filteredResults = data.filter((item) =>
        item.Employee.toLowerCase().includes(term.toLowerCase())
      );
      setResults(filteredResults);
      setShowResults(true);
    } else {
      setResults(data);
      setShowResults(false);
    }
    onSearch(term);
  }, 300);

  const handleChange = (event) => {
    const term = event.target.value;
    setSearchTerm(term);
    handleSearch(term);
  };

  const handleResultClick = (name) => {
    setSearchTerm(name);
    setShowResults(false);
    onSearch(name);
  };

  const handleFocus = () => {
    if (searchTerm.length >= 1) {
      setShowResults(true);
    }
  };

  return (
    <div className="search-bar" style={{ width: '100%', position: 'relative' }}>
      <label htmlFor="employees" style={{ display: 'block', marginBottom: '5px', color: 'white' }}>
        Who are you visiting?
      </label>
      <input
        type="text"
        placeholder="Search by name"
        value={searchTerm}
        onChange={handleChange}
        onFocus={handleFocus}
        style={{
          width: '100%',
          padding: '10px',
          fontSize: '16px',
          border: '1px solid #ccc',
          borderRadius: '3px',
        }}
      />
      {showResults && searchTerm.length >= 1 && results.length > 0 && (
        <ul
          style={{
            position: 'relative',
            top: '100%',
            left: '0',
            width: '100%',
            border: '1px solid #ccc',
            backgroundColor: '#fff',
            listStyle: 'none',
            padding: '0',
            margin: '5px 0 0 0',
            maxHeight: '150px',
            overflowY: 'auto',
            borderRadius: '3px',
            zIndex: '1',
          }}
        >
          {results.map((result, index) => (
            <li
              key={index}
              onMouseDown={() => handleResultClick(result.Employee)}
              style={{
                padding: '10px',
                cursor: 'pointer',
                borderBottom: '1px solid #ccc',
              }}
            >
              {result.Employee}
            </li>
          ))}
        </ul>
      )}
    </div>
  );
};

export default SearchBar;
