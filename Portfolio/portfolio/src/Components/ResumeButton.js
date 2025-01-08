import '../index.css';

const ResumeButton = () => {
    return (
        <div className="resumebutton">
            <a href="/resume.pdf" target="_blank" rel="noopener noreferrer">
                <button>
                    Get My Resume
                </button>
            </a>
        </div>
    );
};

export default ResumeButton;
