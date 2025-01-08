import React from 'react';
import AlecLogo from './AlecLogo';
import SettingsButton from './SettingsButton';

const Navbar = ({ onSettingsClick }) => {
  return (
    <nav className="navbar">
      <AlecLogo onClick={onSettingsClick}/>
      <SettingsButton onClick={onSettingsClick} />
    </nav>
  );
};

export default Navbar;