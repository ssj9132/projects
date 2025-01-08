import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import SearchBar from './SearchEmployee';

const GuestFill = ({ formData: initialFormData }) => {
  const [formData, setFormData] = useState({
    guests: '',
    reason: '',
    guestNames: '',
    ...initialFormData,
  });

  const navigate = useNavigate();

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData({
      ...formData,
      [name]: value
    });
  };

  const handleSubmit = (e) => {
    e.preventDefault();

    console.log(formData);
    navigate('/confirmation', { state: { formData } });
  };

  const handleSearch = (searchTerm) => {
    console.log("Search term:", searchTerm);
  };

  return (
    <form
      className="guest-form"
      onSubmit={handleSubmit}
      style={{
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        width: '100%',
        maxWidth: '800px',
        margin: '0 auto'
      }}
    >
      <div
        className="form-group-horizontal"
        style={{
          display: 'flex',
          justifyContent: 'space-between',
          width: '100%',
          marginBottom: '20px',
        }}
      >
        <div className="form-group" style={{ flex: 1 }}>
          <SearchBar onSearch={handleSearch} />
        </div>
        <div className="form-group" style={{ flex: 1, marginLeft: '10px' , color: 'white'}}>
          <label htmlFor="guests">No. of Guests</label>
          <input
            type="number"
            id="guests"
            name="guests"
            value={formData.guests}
            onChange={handleChange}
            style={{ width: '100%', padding: '10px' }}
          />
        </div>
      </div>
      <div
        className="form-group-horizontal"
        style={{
          display: 'flex',
          justifyContent: 'space-between',
          width: '100%',
          marginBottom: '10px',
        }}
      >
        <div className="form-group" style={{ flex: 1, color: 'white' }}>
          <label htmlFor="reason">Reason for Visit*</label>
          <select
            id="reason"
            name="reason"
            value={formData.reason}
            onChange={handleChange}
            required
            style={{ width: '100%', padding: '13px' }}
          >
            <option value="">Please select</option>
            <option value="Meeting">Meeting</option>
            <option value="Interview">Interview</option>
            <option value="Follow Up">Follow Up</option>
            <option value="Other">Other</option>
          </select>
        </div>
        <div className="form-group" style={{ flex: 1, marginLeft: '10px' , color: 'white'}}>
          <label htmlFor="guestNames">Names of Guests*</label>
          <textarea
            id="guestNames"
            name="guestNames"
            value={formData.guestNames}
            onChange={handleChange}
            placeholder='Please enter guest names on separate lines'
            required={formData.guests > 1}
            disabled={formData.guests === 1}
            style={{ width: '100%', padding: '10px' }}
          />
        </div>
      </div>
      <button type="submit" style={{ padding: '10px 20px', marginTop: '10px' }}>Check In</button>
    </form>
  );
};

export default GuestFill;
