import React from 'react';
import { Link } from 'react-router-dom';
import settingsIcon from '../Assets/settings_icon.png';

const SettingsButton = () => {
  return (
    <Link to="/login" className="settings-button">
      <img src={settingsIcon} alt="Settings" className="settings-icon" />
    </Link>
  );
};

export default SettingsButton;
