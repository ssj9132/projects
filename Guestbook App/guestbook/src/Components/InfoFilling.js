import React, { useState, useEffect } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import '../ContactForm.css'; 

const ContactForm = () => {
  const location = useLocation();
  const [formData, setFormData] = useState({
    name: '',
    phone: '',
    company: '',
    email: ''
  });

  const navigate = useNavigate();

  useEffect(() => {
    if (location.state && location.state.visitor) {
      const visitor = location.state.visitor;
      setFormData({
        name: visitor.Name || '',
        phone: visitor.Phone || '',
        company: visitor.Company || '',
        email: visitor.Email || ''
      });
    }
  }, [location.state]);

  const handleChange = (e) => {
    const { name, value } = e.target;

    if (!location.state || !location.state.visitor) {
      setFormData({
        ...formData,
        [name]: value
      });
    } else if (name !== 'phone') { 
      setFormData({
        ...formData,
        [name]: value
      });
    }
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    console.log('Submitting form with data:', formData);
    navigate('/checkin', { state: { formData } }); 
  };

  return (
    <form className="contact-form" onSubmit={handleSubmit}>
      <div className="form-group-horizontal">
        <div className="form-group">
          <label htmlFor="name">Name*</label>
          <input
            type="text"
            id="name"
            name="name"
            value={formData.name}
            onChange={handleChange}
            placeholder="Please enter your full name."
            required
            className="form-input"
          />
        </div>
        <div className="form-group">
          <label htmlFor="phone">Phone*</label>
          <input
            type="number"
            id="phone"
            name="phone"
            value={formData.phone}
            onChange={handleChange}
            placeholder="Please enter your phone number"
            required
            className="form-input"
            disabled={location.state && location.state.visitor} 
          />
        </div>
      </div>
      <div className="form-group-horizontal">
        <div className="form-group">
          <label htmlFor="company">Company</label>
          <input
            type="text"
            id="company"
            name="company"
            value={formData.company}
            onChange={handleChange}
            placeholder="Please enter company name"
            className="form-input"
          />
        </div>
        <div className="form-group">
          <label htmlFor="email">Email</label>
          <input
            type="email"
            id="email"
            name="email"
            value={formData.email}
            placeholder="Please enter your email"
            onChange={handleChange}
            className="form-input"
          />
        </div>
      </div>
      <button type="submit" className="form-button">Next</button>
    </form>
  );
};

export default ContactForm;
