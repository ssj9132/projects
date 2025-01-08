import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { fetchGuestData } from '../Services/dataService';
import contactImg from '../Assets/contact-img.png';
import nextIcon from '../Assets/next-icon.png';

const SearchBar = () => {
  const [searchTerm, setSearchTerm] = useState('');
  const [results, setResults] = useState([]);
  const [data, setData] = useState([]);
  const navigate = useNavigate();

  useEffect(() => {
    (async () => {
      const visitors = await fetchGuestData();
      setData(visitors);
      setResults(visitors);
    })();
  }, []);

  const handleSearch = (event) => {
    setSearchTerm(event.target.value);
    const filteredResults = data.filter(
      (item) =>
        item.Name.toLowerCase().includes(event.target.value.toLowerCase()) ||
        item.Phone.includes(event.target.value)
    );
    setResults(filteredResults);
  };

  const navigateToRegistration = (visitor) => {
    navigate(`/registration`, { state: { visitor } });
  };

  return (
    <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', marginTop: '30px' }}>
      <div style={{ position: 'relative', width: '700px' }}>
        <input
          type="text"
          placeholder="Search by name or phone number"
          value={searchTerm}
          onChange={handleSearch}
          style={{
            width: '100%',
            padding: '20px'
          }}
        />
        {searchTerm && results.length > 0 && (
          <ul style={{
            position: 'relative',
            top: '5px',
            left: '0',
            right: '0',
            backgroundColor: 'white',
            border: '1px solid #002855',
            maxHeight: '500px',
            overflowY: 'auto',
            margin: '0',
            padding: '0',
            listStyle: 'none'
          }}>
            {results.map((result, index) => (
              <li
                key={index}
                style={{ padding: '10px', cursor: 'pointer', borderBottom: '2px solid #002855', display: 'flex', alignItems: 'center' }}
                onClick={() => navigateToRegistration(result)}
              >
                <img src={contactImg} alt="contact" style={{ marginRight: '10px', height: '30px' }} />
                <div style={{ flexGrow: 1 }}>
                  <b>{result.Name}</b>
                  <div style={{ color: 'grey' }}>{result.Phone}</div>
                </div>
                <img src={nextIcon} alt="next" style={{ marginLeft: '10px', height: '20px' }} />
              </li>
            ))}
          </ul>
        )}
      </div>
    </div>
  );
};

export default SearchBar;
