import React from 'react';
import AlecLogo from './AlecLogo';
import SettingsButton from './SettingsButton';
import SetLoc from './SetLocation';


const navWelcome = ({ onSettingsClick }) => {
  return (
    <nav className="navbar">

      <AlecLogo />  
      <SetLoc />
      <SettingsButton onClick={onSettingsClick} />
    </nav>
  );
};



export default navWelcome;