import React from 'react';
import AlecLogoSmall from '../Assets/alecLogoSmall.png'; 
import BackButton from './BackButton';
import '../index.css';

const OldVisNav = () => {
  return (
    <nav className="oldvisnavbar">
      <BackButton /> 
      <p style = {{fontSize: '40px'}}>Search Guest Book</p>
      <img src={AlecLogoSmall} alt="Alec Logo" style={{ width: '50px', height: 'auto', marginRight: '15px' }} /> 
    </nav>
  );
};

export default OldVisNav;
