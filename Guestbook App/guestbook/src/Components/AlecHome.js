import React from 'react';
import HomeButton from '../Assets/alecHomeButton.png';
import { Link } from 'react-router-dom';


const AlecHome = () => {
  return (
    <div>
      <Link to="/" className="alec-home">
      <img src={HomeButton} alt="Home-Button" />
      </Link>
    </div>
  );
};

export default AlecHome;