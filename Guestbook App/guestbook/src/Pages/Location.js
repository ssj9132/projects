import React, { useState, useEffect } from 'react';
import AlecLogo from '../Components/AlecLogo';
import Select from 'react-select';
import { useNavigate } from 'react-router-dom';
import { fetchLocationData } from '../Services/dataService'; 

const Location = () => {
  const [selectedOption, setSelectedOption] = useState(null);
  const [options, setOptions] = useState([]);
  const navigate = useNavigate();

  useEffect(() => {
    const getLocations = async () => {
      const locations = await fetchLocationData();
      const options = locations.map(location => ({
        value: location,
        label: location
      }));
      setOptions(options);
    };

    getLocations();
  }, []);

  const handleChange = (option) => {
    setSelectedOption(option);
  };

  const handleSave = () => {
    if (selectedOption) {
      localStorage.setItem('selectedLocation', selectedOption.label);
      navigate('/'); 
    } else {
      alert('Please select a location.');
    }
  };

  return (
    <div className="Location">
      <AlecLogo />
      <div className="list" style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', justifyContent: 'center', height: '600px' }}>
        <p style={{color: 'white', fontFamily: 'Arial, sans-serif', fontSize: 'larger'}}>Please select device location*</p>
        <Select 
          options={options} 
          value={selectedOption}
          onChange={handleChange}
          styles={{
            container: (provided) => ({
              ...provided,
              width: '400px',
              marginTop: '20px'
            }),
            control: (provided) => ({
              ...provided,
           
            })
          }}
        />
        <button
          onClick={handleSave}
          style={{
            marginTop: '20px',
            padding: '15px 60px',
            backgroundColor: 'white',
            color: '#002855',
            border: 'none',
            cursor: 'pointer',
            fontSize: '26px'
          }}>
          Save
        </button>
      </div>
    </div>
  );
}

export default Location;
