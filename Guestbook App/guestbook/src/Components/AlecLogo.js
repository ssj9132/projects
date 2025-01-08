import React from 'react';
import logo from '../Assets/alec-logo.png';
import { Link } from 'react-router-dom';

const AlecLogo = () => {
  return (
    <div style={{ marginTop: '40px' }}>
      <Link to="/" className="alec-logo">
        <img 
          src={logo} 
          alt="Logo" 
          style={{ width: '250px', height: 'auto' }} 
        />
      </Link>
    </div>
  );
};

export default AlecLogo;
