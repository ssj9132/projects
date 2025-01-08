import React from 'react';
import backButton from '../Assets/backButton_icon.png';
import { useNavigate } from 'react-router-dom';

const History = () => {
  const navigate = useNavigate();
  const handleGoBack = () => {
    navigate(-1); 
  };

  return (   
    <img 
      src={backButton} 
      alt="back_button" 
      onClick={handleGoBack}
      style={{ cursor: 'pointer', width: '50px', height: 'auto', marginTop: '10px' , marginLeft: '10px'}} />
  );
};

export default History;
