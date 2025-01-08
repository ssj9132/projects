import React from 'react';
import AlecLogoSmall from '../Assets/alecLogoSmall.png'; 
import BackButton from './BackButton';
import '../index.css';

const NewVisNav = () => {
  return (
    <nav className="newvisnavbar">
      <BackButton />
      <p style={{ fontSize: '30px' }} >Welcome to SHAUN JACOB</p>
      <img src={AlecLogoSmall} alt="Alec Logo" style={{ width: '50px', height: 'auto', marginRight: '15px' }}  />
    </nav>
  );
};

export default NewVisNav;
